/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transfer_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:07:39 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/26 06:30:58 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h> //perror

#include "protocol_interpreter.h"
#include "ftp_reply.h"
#include "dtp.h"
#include "../libft/include/libft.h"

pid_t dtp;

static int connect_data(const char *ip, const char *port)
{
	struct addrinfo hints, *result, *rp;
	int sfd;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_NUMERICHOST | AI_NUMERICSERV;
	if (getaddrinfo(ip, port, &hints, &result) != 0)
		return -1;
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;
		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;
		close(sfd);
	}
	freeaddrinfo(result);
	return (rp == NULL ? -1 : sfd);
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
		session->data.sock = connect_data(session->data.host,
			session->data.port);
		if (session->data.sock < 0)
			exit(FTP_CONN_DATA_ERR);
		ret = session->command(session);
		close(session->data.sock);
		exit(ret);
	}
	return 0;
}
