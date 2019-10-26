/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:23:05 by marvin            #+#    #+#             */
/*   Updated: 2019/10/26 12:36:34 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h> //printf

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static void init_session(struct ftp_session *session, int sock,
	struct sockaddr_storage addr, socklen_t addr_len)
{
	session->control.addr = addr;
	session->control.addr_len = addr_len;
	session->control.sock = sock;
	ft_memset(&(session->user), 0, sizeof(session->user));
	ft_memset(&(session->data), 0, sizeof(session->data));
	session->command = NULL;
	session->args = NULL;
	session->data_type = TYPE_ASCII;
	session->pipefd = -1;
	send_dtp_reply(session->control.sock, FTP_CONN_CTRL_READY);
}

int session_manager(int sock, struct sockaddr_storage addr, socklen_t addr_len)
{
	struct ftp_session session;
	int status, pipefd[2];
	pid_t user;

	init_session(&session, sock, addr, addr_len);
	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR) /* sth more adapted */
		exit(FTP_FILE_LOCAL_ERR);
	while (1) {
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
			if (read(pipefd[0], &session, sizeof(session) + 1)
				!= sizeof(session)) {
				break ;
			}
			close(pipefd[0]);
		}
	}
	server_log("closed socket", (struct sockaddr *)&session.control.addr,
		session.control.addr_len);
	close_session(&session);
	close(pipefd[0]);
	return (status == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
