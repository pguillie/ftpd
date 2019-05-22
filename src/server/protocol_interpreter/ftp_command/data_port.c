/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_port.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:45:27 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 12:13:56 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

static int data_port_syntax(const char *str)
{
	size_t i;
	int comma;

	i = 0;
	comma = 5;
	while (str[i] && (isdigit(str[i]) || (str[i] == ',' && comma-- > 0 ))) {
		i++;
	}
	return (!comma & !str[i]);
}

static int set_data_addr(const char *data_addr, const char *data_port)
{
	in_addr_t addr;
	int port;

	addr = inet_addr(data_addr);
	port = atoi(data_port) * 256;
	while (*data_port != ',')
		data_port++;
	port += atoi(data_port + 1);
	if (addr == INADDR_NONE || port > USHRT_MAX || port < 0)
		return (-1);
	client.data.sin_port = htons(port);
	client.data.sin_addr.s_addr = addr;
	return (0);
}

pid_t dtp;
int dtp_io[2];

int data_port(int control_sock)
{
	char *addr;
	int comma;
	size_t i;

	if (!client.user) {
		send_reply(control_sock, FTP_AUTH_USER_ERR);
		return (1);
	}
	addr = strtok(NULL, " ");
	if (addr == NULL || strtok(NULL, " ") != NULL
		|| !data_port_syntax(addr)) {
		send_reply(control_sock, FTP_SYNT_ARG_ERR);
		return (1);
	}
	comma = 0;
	i = 0;
	while (comma < 4) {
		if (addr[i] == ',')
			addr[i] = (++comma < 4 ? '.' : '\0');
		i++;
	}
	if (set_data_addr(addr, addr + i) < 0) {
		send_reply(control_sock, FTP_SYNT_ARG_ERR);
		return (1);
	}
	printf("write: %lu (struct sockaddr_in)\n", sizeof(client.data));
	/* write(1, &(client.data), sizeof(client.data)); */
	/* write(dtp_io[1], &(client.data), sizeof(client.data)); */
	/* kill(dtp, SIGUSR1); */
	/* send_reply(control_sock, FTP_SYNT_OK); */
	/* return (0); */
	char dtp_ret[3+1];
	write(dtp_io[1], &(uint16_t){sizeof(client.data) + 1}, 2);
	write(dtp_io[1], "p", 1);
	write(dtp_io[1], &(client.data), sizeof(client.data));
	read(dtp_io[0], dtp_ret, 3);
	dtp_ret[3] = '\0';
	send_reply(control_sock, dtp_ret);
	return (0);
}
