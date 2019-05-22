/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 09:09:49 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/20 16:33:42 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"
#include "server/protocol_interpreter.h"

struct ftp_client client;

static int create_server(const char *port)
{
	int lsock;
	struct sockaddr_in addr;
	int true = 1;

	lsock = socket(AF_INET, SOCK_STREAM, 0);
	if (lsock < 0) {
		fprintf(stderr, "Error: socket\n");
		return (-1);
	}
	setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port)); // atoi
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (bind(lsock, (struct sockaddr *)&addr, sizeof(addr))) {
		fprintf(stderr, "Error: bind\n");
		return (-1);
	}
	if (listen(lsock, 3) < 0) {
		fprintf(stderr, "Error: listen\n");
		return (-1);
	}
	return (lsock);
}

static void chld_handler(int sig __attribute__((unused)))
{
	wait4(-1, NULL, 0, NULL);
}

static void init_client_info(struct sockaddr_in addr)
{
	client.user = NULL;
	client.ctrl = addr;
	client.data = addr;
}

int server(const char *port)
{
	int lsock, control_sock;
	struct sockaddr_in addr;
	socklen_t len;
	pid_t pi;

	lsock = create_server(port);
	if (lsock < 0)
		return (1);
	if (signal(SIGCHLD, chld_handler) == SIG_ERR)
		return (2);
	while (1) {
		control_sock = accept(lsock, (struct sockaddr *)&addr, &len);
		if (control_sock < 0)
			fprintf(stderr, "Error: accept\n");
		pi = fork();
		if (pi == 0) {
			close(lsock);
			init_client_info(addr);
			protocol_interpreter(control_sock);
		} else {
			if (pi < 0)
				send_reply(control_sock, FTP_CONN_CTRL_ERR);
			close(control_sock);
		}
	}
	close(lsock);
	return (0);
}
