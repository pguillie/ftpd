/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:19:41 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:23:00 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static int set_type_ascii(struct ftp_session *session, char *format)
{
	char f;

	f = '\0';
	if (format == NULL)
		f = 'N';
	else if (ft_strlen(format) == 1)
		f = ft_toupper(format[0]);
	if (f != 'N') {
		send_reply(session->control.sock, (f == 'T' || f == 'C')
			? FTP_SYNT_NOT_IMPL_PARA
			: FTP_SYNT_ERR);
		return 1;
	}
	session->data_type = TYPE_ASCII;
	send_reply(session->control.sock, FTP_SYNT_CMD_OK, "TYPE");
	return 0;
}

static int set_type_image(struct ftp_session *session, char *param)
{
	if (param != NULL) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	session->data_type = TYPE_IMAGE;
	send_reply(session->control.sock, FTP_SYNT_CMD_OK, "TYPE");
	return 0;
}

static int set_type_ebcdic(struct ftp_session *session,
	char *format __attribute__((unused)))
{
	send_reply(session->control.sock, FTP_SYNT_NOT_IMPL);
	return 1;
}

static int set_type_local(struct ftp_session *session,
	char *size __attribute__((unused)))
{
	send_reply(session->control.sock, FTP_SYNT_NOT_IMPL);
	return 1;
}

int ftp_type(struct ftp_session *session)
{
	char *type, *param;

	if (!session->user) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	type = ft_strtok(session->args, " ");
	param = ft_strtok(NULL, " ");
	if (type == NULL) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	type[0] = ft_toupper(type[0]);
	if (ft_strcmp(type, "A") == 0)
		return set_type_ascii(session, param);
	else if (ft_strcmp(type, "E") == 0)
		return set_type_ebcdic(session, param);
	else if (ft_strcmp(type, "I") == 0)
		return set_type_image(session, param);
	else if (ft_strcmp(type, "L") == 0)
		return set_type_local(session, param);
	send_reply(session->control.sock, FTP_SYNT_ERR);
	return 1;
}
