/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transfer_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:07:39 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:27:19 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h> //perror

#include "protocol_interpreter.h"
#include "ftp_reply.h"
#include "dtp.h"

pid_t dtp;

static int connect_data(struct sockaddr_in addr)
{
	int sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("Error: dtp socket");
		return -1;
	}
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error: dtp connect");
		return -1;
	}
	return sock;
}

int data_transfer_process(struct ftp_session *session)
{
	int ret;

	if (dtp >= 0) {
		send_reply(session->control.sock, FTP_FILE_TRANSFR_ERR);
		return -1;
	}
	dtp = fork();
	if (dtp < 0) {
		fprintf(stderr, "Error: DTP fork\n");
		send_reply(session->control.sock, FTP_FILE_LOCAL_ERR);
		return -1;
	} else if (dtp == 0) {
		if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
			exit(FTP_FILE_LOCAL_ERR);
		session->data.sock = connect_data(session->data.addr);
		if (session->data.sock < 0)
			exit(FTP_CONN_DATA_ERR);
		ret = session->command(session);
		exit(ret);
	}
	return 0;
}
