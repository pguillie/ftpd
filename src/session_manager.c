/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:23:05 by marvin            #+#    #+#             */
/*   Updated: 2019/10/04 14:07:17 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <pwd.h>
#include <grp.h>

#include <stdio.h> //printf

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static int init_session(struct ftp_session *session, struct connection control)
{
	session->control = control;
	session->data = control;
	session->data_type = TYPE_ASCII;
	if (send_reply(session->control.sock, FTP_CONN_CTRL_READY) != 0)
		return -1;
	return 0;
}

static int login(struct passwd *pwd)
{
	if (pwd->pw_uid == 0
		|| setgid(pwd->pw_gid) < 0
		|| initgroups(pwd->pw_name, pwd->pw_gid) < 0
		|| setuid(pwd->pw_uid) < 0
		|| chdir(pwd->pw_dir) < 0)
		return -1;
	return 0;
}

static int auth(int pipefd, struct ftp_session *session, struct passwd **pwd)
{
	char login[256];
	ssize_t n;

	n = read(pipefd, session, sizeof(struct ftp_session));
	if (n == 0)
		return 0;
	else if (n < 0 || (size_t)n < sizeof(struct ftp_session))
		return -1;
	n = read(pipefd, login, sizeof(login));
	if (n < 1)
		return -1;
	login[n] = '\0';
	*pwd = getpwnam(login);
	return 1;
}

int session_manager(int sock, struct sockaddr_in addr)
{
	struct ftp_session session;
	int ret, quit, pipefd[2];
	pid_t pi;

	struct passwd *pwd = NULL;

	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR) /* sth more adapted? */
		exit(EXIT_FAILURE);
	if (init_session(&session, (struct connection){addr, sock}) == -1)
		die(&session);
	quit = 0;
	while (!quit) {
		if (pipe(pipefd) == -1)
			die(&session);
		pi = fork();
		if (pi < 0) {
			die(&session);
		} else if (pi == 0) {
			close(pipefd[0]);
			if (!pwd)
				session.auth = 0;
			else if (login(pwd) < 0)
				die(&session);
			else
				session.auth = 1;
 			session.pipefd = pipefd[1];
			protocol_interpreter(&session);
		}
		close(pipefd[1]);
		wait4(pi, &ret, 0, NULL);
		printf("Child exited with status: %d\n", ret);
		if (WIFEXITED(ret) && ret == EXIT_SUCCESS) {
			ret = auth(pipefd[0], &session, &pwd);
			if (ret == -1)
				send_reply(session.control.sock, FTP_CONN_CTRL_ERR);
			else if (ret == 1)
				send_reply(session.control.sock,
					pwd ? FTP_AUTH_OK : FTP_AUTH_ERR);
			quit = (ret == 1 ? 0 : 1);
		} else {
			quit = 1;
		}
		close(pipefd[0]);
	}
	close_session(&session);
	return (WIFEXITED(ret) ? ret : EXIT_FAILURE);
}
