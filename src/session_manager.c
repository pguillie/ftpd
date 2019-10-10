/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:23:05 by marvin            #+#    #+#             */
/*   Updated: 2019/10/10 10:31:33 by pguillie         ###   ########.fr       */
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
	if (!pwd || pwd->pw_uid == 0)
		return 0;
	if (setgid(pwd->pw_gid) < 0
		|| initgroups(pwd->pw_name, pwd->pw_gid) < 0
		|| setuid(pwd->pw_uid) < 0
		|| chdir(pwd->pw_dir) < 0)
		return -1;
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
	do {
		if (pipe(pipefd) == -1)
			die(&session);
		pi = fork();
		if (pi < 0) {
			die(&session);
		} else if (pi == 0) {
			close(pipefd[0]);
			session.auth = login(pwd);
			if (session.auth < 0)
				die(&session);
 			session.pipefd = pipefd[1];
			protocol_interpreter(&session);
		}
		close(pipefd[1]);
		wait4(pi, &ret, 0, NULL);
		if (WIFEXITED(ret) && ret == EXIT_SUCCESS) {
			ret = auth(pipefd[0], &session, &pwd);
			quit = (ret == 1 ? 0 : 1);
		} else {
			quit = 1;
		}
		close(pipefd[0]);
	} while (!quit);
	close_session(&session);
	return (WIFEXITED(ret) ? ret : EXIT_FAILURE);
}
