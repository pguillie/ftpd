/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_port.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:45:27 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/26 07:04:40 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static int is_valid_syntax(const char *addr)
{
	size_t i, byte;

	byte = 0;
	while (*addr) {
		if (*addr == ',')
			addr += 1;
		i = 0;
		while (ft_isdigit(addr[i]))
			i++;
		if (!i || ft_atoi(addr) > 255 || (addr[i] && addr[i] != ','))
			return 0;
		addr += i;
		byte++;
	}
	if (byte != 6)
		return 0;
	return 1;
}

static void set_host(char *host, const char *addr)
{
	size_t i;
	int byte;

	i = 0;
	byte = 0;
	while (byte < 4) {
		if (addr[i] == ',') {
			byte++;
			host[i] = (byte < 4 ? '.' : '\0');
		} else {
			host[i] = addr[i];
		}
		i++;
	}
}

static void set_port(char *port, const char *addr)
{
	size_t i;
	int n;

	for (i = 0; i < 4; i++)
		while (*addr++ != ',') ;
	n = ft_atoi(addr);
	while (*addr++ != ',') ;
	n = n * 256 + ft_atoi(addr);
	i = 1;
	while (n / (i * 10) > 0)
		i *= 10;
	while (i) {
		*port++ = n / i + '0';
		n %= i;
		i /= 10;
	}
	*port = '\0';
}

int ftp_port(struct ftp_session *session)
{
	char *addr;

	if (!session->user.pw_uid) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	addr = session->args;
	if (addr == NULL || !is_valid_syntax(addr)) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	set_host(session->data.host, addr);
	set_port(session->data.port, addr);
	send_reply(session->control.sock, FTP_SYNT_CMD_OK, "PORT");
	return 0;
}
