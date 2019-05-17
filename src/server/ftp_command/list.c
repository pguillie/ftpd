/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 11:30:09 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/17 12:49:15 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

struct ftp_client client;

static int connect_data(int control_sock)
{
	int data_sock;

	send_reply(control_sock, FTP_FILE_DATA_OK);
	data_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (data_sock < 0)
		return (-1);
	if (connect(data_sock, (struct sockaddr *)&(client.data),
			sizeof(client.data)) < 0)
		return (-1);
	return (data_sock);
}

static int ls(int control_sock, int data_sock)
{
	(void)control_sock;
	send_reply(data_sock, "Hello, World!");
	return (0);
}

int list(int control_sock)
{
	int data_sock, ret;

	if (!client.user) {
		send_reply(control_sock, FTP_AUTH_USER_ERR);
		return (1);
	}
	data_sock = connect_data(control_sock);
	if (data_sock < 0) {
		send_reply(control_sock, FTP_CONN_DATA_OPEN_ERR);
		return (1);
	}
	ret = ls(control_sock, data_sock);
	if (ret == 0)
		send_reply(control_sock, FTP_CONN_DATA_CLOSE);
	close(data_sock);
	return (ret);
}
