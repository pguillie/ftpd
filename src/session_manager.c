/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:23:05 by marvin            #+#    #+#             */
/*   Updated: 2019/09/27 11:59:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h> //printf

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static void init_session(struct ftp_session *session, int sock,
	struct sockaddr_in addr)
{
	session->control = (struct connection){addr, sock};
	ft_memset(&(session->user), 0, sizeof(session->user));
	ft_memset(&(session->data), 0, sizeof(session->data));
	session->command = NULL;
	session->args = NULL;
	session->data_type = TYPE_ASCII;
	session->pipefd = -1;
	send_dtp_reply(session->control.sock, FTP_CONN_CTRL_READY);
}

int session_manager(int sock, struct sockaddr_in addr)
{
	struct ftp_session session;
	int status, pipefd[2];
	pid_t user;

	init_session(&session, sock, addr);
	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR) /* sth more adapted */
		exit(FTP_FILE_LOCAL_ERR);
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
			close(pipefd[1]);
			wait4(user, &status, 0, NULL);
			printf("Child exited with status: %d\n", status);
			if (read(pipefd[0], &session, sizeof(session) + 1)
				!= sizeof(session)) {
				printf("Read more or less bytes than session's size!\n");
				break ;
			}
			close(pipefd[0]);
			printf("received struct! USER = %s\n", session.user.pw_name);
		}
	}
	close_session(&session);
	close(pipefd[0]);
	return (status == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
