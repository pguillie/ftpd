/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:23:05 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/24 14:31:32 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static int init_session(struct ftp_session *session, int sock,
	struct sockaddr_storage addr, socklen_t addr_len)
{
	session->control.addr = addr;
	session->control.addr_len = addr_len;
	session->control.sock = sock;
	ft_memset(&(session->data), 0, sizeof(session->data));
	session->command = NULL;
	session->args = NULL;
	session->data_type = TYPE_ASCII;
	if (getuid() != 0) {
		if (!getcwd(session->home, PATH_MAX))
			return -1;
	}
	if (send_reply(session->control.sock, FTP_CONN_CTRL_READY) != 0)
		return -1;
	return 0;
}

static void run_session(struct ftp_session *session, int *pipefd,
	struct passwd *pwd)
{
	close(pipefd[0]);
	if (getuid() == 0)
		session->auth = login(pwd);
	else
		session->auth = 1;
	if (session->auth < 0)
		die(session);
	session->pipefd = pipefd[1];
	protocol_interpreter(session);
}

static int manage_session(struct ftp_session *session)
{
	struct passwd *pwd;
	int pipefd[2], status, quit;
	pid_t pi;

	pwd = NULL;
	do {
		if (pipe(pipefd) == -1)
			die(session);
		pi = fork();
		if (pi < 0)
			die(session);
		else if (pi == 0)
			run_session(session, pipefd, pwd);
		close(pipefd[1]);
		wait4(pi, &status, 0, NULL);
		if (WIFEXITED(status) && status == EXIT_SUCCESS)
			quit = (auth(pipefd[0], session, &pwd) < 0);
		else
			quit = 1;
		close(pipefd[0]);
	} while (!quit);
	return (WIFEXITED(status) ? status : EXIT_FAILURE);
}

int session_manager(int sock, struct sockaddr_storage addr, socklen_t addr_len)
{
	struct ftp_session session;
	int ret;

	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR
		|| signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (init_session(&session, sock, addr, addr_len) == -1)
		die(&session);
	ret = manage_session(&session);
	close_session(&session);
	return ret;
}
