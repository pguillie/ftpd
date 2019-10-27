/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:51:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/27 06:59:25 by pguillie         ###   ########.fr       */
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
int dtp_ctrl_sock;

static void dtp_exit_status(int sig __attribute__((unused)))
{
	int ftp_reply_code;

	wait4(dtp, &ftp_reply_code, 0, NULL);
	dtp = -1;
	if (WIFEXITED(ftp_reply_code))
		send_reply(dtp_ctrl_sock, WEXITSTATUS(ftp_reply_code));
	else
		send_reply(dtp_ctrl_sock, FTP_FILE_LOCAL_ERR);
}

int protocol_interpreter(struct ftp_session *session)
{
	char line[128];//
	int ret;

	if (signal(SIGCHLD, dtp_exit_status) == SIG_ERR)
		die(session);
	dtp_ctrl_sock = session->control.sock;
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
