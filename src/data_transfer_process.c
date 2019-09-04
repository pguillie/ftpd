/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transfer_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:07:39 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/05 21:10:26 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"
//
struct ftp_client client;
//
pid_t dtp;

typedef int (*dtp_function)(const char *file);

dtp_function dtp_command[] = {
	[DTP_RETR] = &dtp_retr,
	[DTP_STOR] = &dtp_stor,
	[DTP_LIST] = &dtp_list
};

static int connect_data(struct sockaddr_in data_sockaddr)
{
	int data_sock;

	data_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (data_sock < 0) {
		perror("Error: dtp socket");
		return (-1);
	}
	if (connect(data_sock, (struct sockaddr *)&(data_sockaddr),
			sizeof(data_sockaddr)) < 0) {
		perror("Error: dtp connect");
		return (-1);
	}
	return (data_sock);
}

int data_transfer_process(enum e_dtp_type id, const char *file)
{
	int ret;

	if (dtp >= 0) {
		send_reply(client.control.sock, FTP_FILE_TRANSFR_ERR);
		return (-1);
	}
	dtp = fork();
	if (dtp < 0) {
		fprintf(stderr, "Error: DTP fork\n");
		send_reply(client.control.sock, FTP_FILE_LOCAL_ERR);
		return (-1);
	} else if (dtp == 0) {
		if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
			exit(FTP_FILE_LOCAL_ERR);
		client.data.sock = connect_data(client.data.addr);
		if (client.data.sock < 0)
			exit(FTP_CONN_DATA_ERR);
		ret = dtp_command[id](file);
		exit(ret);
	}
	return (0);
}
