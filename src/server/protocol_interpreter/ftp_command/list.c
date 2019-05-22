/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 11:30:09 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 13:18:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

/* static int connect_data(int control_sock) */
/* { */
/* 	int data_sock; */

/* 	send_reply(control_sock, FTP_FILE_DATA_OK); */
/* 	data_sock = socket(AF_INET, SOCK_STREAM, 0); */
/* 	if (data_sock < 0) */
/* 		return (-1); */
/* 	if (connect(data_sock, (struct sockaddr *)&(client.data), */
/* 			sizeof(client.data)) < 0) */
/* 		return (-1); */
/* 	return (data_sock); */
/* } */

/* static int ls(int control_sock, int data_sock) */
/* { */
/* 	(void)control_sock; */
/* 	send_reply(data_sock, "Hello, World!"); */
/* 	return (0); */
/* } */

/* int list(int control_sock) */
/* { */
/* 	int data_sock, ret; */

/* 	if (!client.user) { */
/* 		send_reply(control_sock, FTP_AUTH_USER_ERR); */
/* 		return (1); */
/* 	} */
/* 	data_sock = connect_data(control_sock); */
/* 	if (data_sock < 0) { */
/* 		send_reply(control_sock, FTP_CONN_DATA_OPEN_ERR); */
/* 		return (1); */
/* 	} */
/* 	ret = ls(control_sock, data_sock); */
/* 	if (ret == 0) */
/* 		send_reply(control_sock, FTP_CONN_DATA_CLOSE); */
/* 	close(data_sock); */
/* 	return (ret); */
/* } */

int dtp_io[2];

int list(int control_sock)
{
	char *path;
	char dtp_ret[3+1];

	path = strtok(NULL, " ");
	if (path == NULL || strtok(NULL, " ") != NULL) {
		send_reply(control_sock, FTP_SYNT_ARG_ERR);
		return (1);
	}
	write(dtp_io[1], &(uint16_t){1 + strlen(path)}, 2);
	write(dtp_io[1], "l", 1);
	write(dtp_io[1], path, strlen(path));
	if (read(dtp_io[0], dtp_ret, 3) < 0)
		perror("read DTP");
	dtp_ret[3] = '\0';
	send_reply(control_sock, dtp_ret);
	return (0);
}
