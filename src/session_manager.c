/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:23:05 by marvin            #+#    #+#             */
/*   Updated: 2019/10/03 11:27:59 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h> //printf

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static int init_session(struct ftp_session *session, int sock,
	struct sockaddr_in addr)
{
	session->lnmax = sysconf(_SC_LOGIN_NAME_MAX);
	if (lnmax == -1)
		lnmax = 128;
	session->user.login = malloc(lnmax);
	session->user.name = malloc(lnmax);
	if (session->user.login == NULL || session->user.name == NULL)
		return -1;
	ft_memset(&(session->user.login), '\0', lnmax);
	ft_memset(&(session->user.name), '\0', lnmax);
	session->user.uid = 0;
	session->user.gid = 0;
	session->control = (struct connection){addr, sock};
	session->data_type = TYPE_ASCII;
	if (send_dtp_reply(session->control.sock, FTP_CONN_CTRL_READY) != 0)
		return -1;
	return 0;
}

int session_manager(int sock, struct sockaddr_in addr)
{
	struct ftp_session session;
	int status, pipefd[2];
	pid_t user;

	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR) /* sth more adapted? */
		exit(EXIT_FAILURE);
	if (init_session(&session, sock, addr) == -1)
		die(&session);
	while (1) {
		printf("fork!\n");
		if (pipe(pipefd) == -1)
			die(&session);
		user = fork();
		if (user < 0) {
			die(&session);
		} else if (user == 0) {
			close(pipefd[0]);
			session.pipefd = pipefd[1];
			protocol_interpreter(&session);
		} else {
			ssize_t n;
			close(pipefd[1]);
			wait4(user, &status, 0, NULL);
			printf("Child exited with status: %d\n", status);
			if (!WIFEXITED(status) || status != EXIT_SUCCESS)
				break ;
			n = read(pipefd[0], &session, sizeof(session) + 1);
			if (n == 0)
				break ;
			else if (n != sizeof(session)) {
				printf("Read more or less bytes than session's size!\n");
				status = EXIT_FAILURE;
				break ;
			}
			close(pipefd[0]);
			printf("received struct! USER = %s\n", session.user.login);
		}
	}
	close_session(&session);
	close(pipefd[0]);
	return (WIFEXITED(status) ? status : EXIT_FAILURE);
}
