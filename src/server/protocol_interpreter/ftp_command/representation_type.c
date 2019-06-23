/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   representation_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:19:41 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/23 14:30:27 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

static int set_type_ascii(char *code)
{
	char c;

	if (code != NULL) {
		if (code[1] != '\0') {
			send_reply(client.control.sock, FTP_SYNT_ERR);
			return (1);
		}
		c = ft_toupper(code[0]);
	} else {
		c = 'N';
	}
	if (c == 'T' || c == 'C') {
		send_reply(client.control.sock, FTP_SYNT_NOT_IMPL_PARA);
		return (1);
	} else if (c != 'N') {
	}
	client.binary = 0;
	send_reply(client.control.sock, FTP_SYNT_CMD_OK, "TYPE");
	return (0);
}

static int set_type_image(char *code)
{
	if (code != NULL) {
		send_reply(client.control.sock, FTP_SYNT_ERR);
		return (1);
	}
	client.binary = 1;
	send_reply(client.control.sock, FTP_SYNT_CMD_OK, "TYPE");
	return (0);
}

int representation_type(char *arguments)
{
	char *type, *code;

	if (!client.user) {
		send_reply(client.control.sock, FTP_AUTH_ERR);
		return (1);
	}
	type = strtok(arguments, " ");
	code = strtok(NULL, " ");
	if (type == NULL) {
		send_reply(client.control.sock, FTP_SYNT_ERR);
		return (1);
	}
	type[0] = ft_toupper(type[0]);
	if (ft_strcmp(type, "E") == 0 || ft_strcmp(type, "L") == 0) {
		send_reply(client.control.sock, FTP_SYNT_NOT_IMPL_PARA);
		return (1);
	}
	if (strcmp(type, "A") == 0)
		return (set_type_ascii(code));
	if (strcmp(type, "I") == 0)
		return (set_type_image(code));
	send_reply(client.control.sock, FTP_SYNT_ERR);
	return (1);
}
