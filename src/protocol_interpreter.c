/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:51:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/26 12:35:37 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <grp.h>

#include "protocol_interpreter.h"
#include "dtp.h"
#include "../libft/include/libft.h"

pid_t dtp = -1;

static void dtp_exit_status(int sig __attribute__((unused)))
{
	int ftp_reply_code;

	wait4(dtp, &ftp_reply_code, 0, NULL);
	dtp = -1;
	if (WIFEXITED(ftp_reply_code))
		send_dtp_reply(-1, WEXITSTATUS(ftp_reply_code));
	else
		send_dtp_reply(-1, FTP_FILE_LOCAL_ERR);
}

static int log_user(struct ftp_session *session)
{
	if (session->user.pw_uid == 0 || session->user.pw_gid == 0
		|| setgid(session->user.pw_gid) < 0
		|| initgroups(session->user.pw_name, session->user.pw_gid) < 0
		|| setuid(session->user.pw_uid) < 0) {
		ft_memset(&(session->user), 0, sizeof(session->user));
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	if (chdir(session->user.pw_dir) < 0)
		die(session);
	send_reply(session->control.sock, FTP_AUTH_OK);
	return 0;
}

int protocol_interpreter(struct ftp_session *session)
{
	char line[128];
	int ret;

	if (signal(SIGCHLD, dtp_exit_status) == SIG_ERR)
		die(session);
	if (session->user.pw_uid != 0)
		log_user(session);
	while ((ret = recv_command(session->control.sock, line,
				sizeof(line))) > 0) {
		if (ret > 1) {
			send_reply(session->control.sock, FTP_SYNT_TOO_LONG);
			continue ;
		}
		server_log(line, (struct sockaddr *)&session->control.addr,
			session->control.addr_len);
		if (set_command(session, line) != 0)
			send_reply(session->control.sock, FTP_SYNT_ERR);
		else if (session->command(session) < 0)
			die(session);
	}
	close_session(session);
	exit(ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
