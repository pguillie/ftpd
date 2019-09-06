/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:51:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 08:01:53 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>

#include "protocol_interpreter.h"
#include "ftp_struct.h"
#include "dtp.h"
#include "../libft/include/libft.h"

pid_t dtp = -1;

static void dtp_reply(int sock, enum ftp_reply_code rep_idx)
{
	static int _sock;

	if (sock >= 0)
		_sock = sock;
	send_reply(_sock, rep_idx);
}

static void dtp_exit_status(int sig __attribute__((unused)))
{
	int ftp_reply_code;

	wait4(dtp, &ftp_reply_code, 0, NULL);
	dtp = -1;
	if (WIFEXITED(ftp_reply_code))
		dtp_reply(-1, WEXITSTATUS(ftp_reply_code));
	else
		dtp_reply(-1, FTP_FILE_LOCAL_ERR);

}

static int init_session(struct ftp_session *session, int sock,
	struct sockaddr_in addr)
{
	session->user = NULL;
	session->control = (struct connection){addr, sock};
	ft_memset(&(session->data), 0, sizeof(session->data));
	session->command = NULL;
	session->args = NULL;
	session->data_type = TYPE_ASCII;
	dtp_reply(session->control.sock, FTP_CONN_CTRL_READY);
	if (signal(SIGCHLD, dtp_exit_status) == SIG_ERR)
		return -1;
	return 0;
}

int protocol_interpreter(int sock, struct sockaddr_in addr)
{
	struct ftp_session session;
	char line[128];
	int ret;

	if (init_session(&session, sock, addr) < 0)
		die(&session);
	while ((ret = recv_command(session.control.sock, line,
				sizeof(line))) > 0) {
		if (ret > 1) {
			send_reply(session.control.sock, FTP_SYNT_TOO_LONG);
			continue ;
		}
		if (set_command(&session, line) != 0)
			send_reply(session.control.sock, FTP_SYNT_ERR);
		else if (session.command(&session) < 0)
			die(&session);
	}
	close_session(&session);
	return (ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
