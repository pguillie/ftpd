/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_port.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:45:27 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:22:28 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static int port_syntax(const char *str)
{
	size_t i;
	int comma;

	i = 0;
	comma = 5;
	while (str[i]
		&& (ft_isdigit(str[i]) || (str[i] == ',' && comma-- > 0))) {
		i++;
	}
	return (!comma & !str[i]);
}

static int set_host_port(struct ftp_session *session, char *host_port)
{
	in_addr_t host;
	int port;
	size_t comma, i;

	comma = 0;
	i = 0;
	while (comma < 4) {
		if (host_port[i] == ',')
			host_port[i] = (++comma < 4 ? '.' : '\0');
		i++;
	}
	host = inet_addr(host_port);
	port = ft_atoi(host_port + i) * 256;
	while (host_port[i] != ',')
		i++;
	port += ft_atoi(host_port + i + 1);
	if (host == INADDR_NONE || port < 0 || port > USHRT_MAX)
		return -1;
	session->data.addr.sin_family = AF_INET;
	session->data.addr.sin_port = htons(port);
	session->data.addr.sin_addr.s_addr = host;
	return 0;
}

int ftp_port(struct ftp_session *session)
{
	char *host_port;

	if (!session->user) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	host_port = ft_strtok(session->args, " ");
	if (!host_port || ft_strtok(NULL, " ") || !port_syntax(host_port)) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	if (set_host_port(session, host_port) != 0) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return -1;
	}
	send_reply(session->control.sock, FTP_SYNT_CMD_OK, "PORT");
	return 0;
}
