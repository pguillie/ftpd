/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_reply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:46:43 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 07:45:43 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

#include "protocol_interpreter.h"
#include "ftp_reply.h"
#include "../libft/include/libft.h"

const char * const ftp_reply_message[] = {
	[FTP_SYNT_OK] = "200 Command okay.",
	[FTP_SYNT_CMD_OK] = "200 * command successfull.",
	[FTP_SYNT_ERR] = "500 Syntax error.",
	[FTP_SYNT_TOO_LONG] = "500 Command line too long.",
	[FTP_SYNT_NOT_IMPL] = "502 Command not implemented.",
	[FTP_SYNT_NOT_IMPL_PARA] = "504 Command not implemented for that parameter.",
	[FTP_INFO_SYS_TYPE] = "215 * system type.",
	[FTP_CONN_CTRL_READY] = "220 Service ready for new user.",
	[FTP_CONN_CTRL_CLOSE] = "221 Service closing control connection.",
	[FTP_CONN_DATA_CLOSE] = "226 Transfer successfull, closing data connection.",
	[FTP_CONN_ABORT_OK] = "226 Transfer successfully aborted.",
	[FTP_CONN_CTRL_ERR] = "421 Service not available. Closing control connection.",
	[FTP_CONN_DATA_ERR] = "425 Can't open data connection.",
	[FTP_CONN_ABORT_ERR] = "426 Connection closed, transfer aborted.",
	[FTP_AUTH_OK] = "230 User logged in, proceed.",
	[FTP_AUTH_ERR] = "530 Not logged in.",
	[FTP_FILE_RETR_OPEN] = "150 Preparing file retrieval.",
	[FTP_FILE_STOR_OPEN] = "150 Preparing file storage.",
	[FTP_FILE_LIST_OPEN] = "150 Preparing directory listing.",
	[FTP_FILE_CWD_OK] = "250 Working directory changed.",
	[FTP_FILE_PWD_OK] = "257 \"*\"",
	[FTP_FILE_LIST_ERR] = "450 Unable to list directory.",
	[FTP_FILE_TRANSFR_ERR] = "451 Another transfer process is running.",
	[FTP_FILE_LOCAL_ERR] = "451 Critical error encountered. Transfer aborted.",
	[FTP_FILE_ERR] = "550 File unavailable.",
	[FTP_FILE_CWD_ERR] = "550 Unable to change working directory.",
	[FTP_FILE_PWD_ERR] = "550 Working directory unavailable."
};

static int reply_out(int sock, struct reply_buffer *rep)
{
	ft_memcpy(rep->buf + rep->i, "\r\n", 2);
	if (send(sock, rep->buf, rep->i + 2, 0) < 0)
		return -1;
	ft_memset(rep->buf, ' ', 4);
	rep->i = 4;
	return 0;
}

static int reply_in(int sock, struct reply_buffer *rep, char c)
{
	if (rep->i == sizeof(rep->buf) - 2) {
		if (rep->hyphen) {
			rep->buf[3] = '-';
			rep->hyphen = 0;
		}
		if (reply_out(sock, rep) < 0)
			return -1;
	}
	rep->buf[rep->i++] = c;
	return 0;
}

static int reply_arg(int sock, struct reply_buffer *rep,
	const char *arg)
{
	while (*arg)
		if (reply_in(sock, rep, *arg++) < 0)
			return -1;
	return 0;
}

int send_reply(int sock, enum ftp_reply_code rep_idx, ...)
{
	va_list ap;
	const char *rep_msg;
	struct reply_buffer rep;

	va_start(ap, rep_idx);
	rep_msg = ftp_reply_message[rep_idx];
	rep.i = 0;
	rep.hyphen = 1;
	while (*rep_msg) {
		if (*rep_msg == '*'
			? reply_arg(sock, &rep, va_arg(ap, char *)) < 0
			: reply_in(sock, &rep, *rep_msg) < 0) {
			write(1, "exit\n", 6);
			return -1;
		}
		rep_msg++;
	}
	ft_memcpy(rep.buf, ftp_reply_message[rep_idx], 3);
	if (reply_out(sock, &rep) < 0)
		return -1;
	va_end(ap);
	return 0;
}
