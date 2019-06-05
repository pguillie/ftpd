/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 09:09:49 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/30 17:31:09 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"
#include "server/protocol_interpreter.h"

static void child_handler(int sig __attribute__((unused)))
{
	wait4(-1, NULL, 0, NULL);
}

static int create_server(const char *port)
{
	int lsock;
	struct sockaddr_in addr;

	lsock = socket(AF_INET, SOCK_STREAM, 0);
	if (lsock < 0) {
		fprintf(stderr, "Error: socket\n");
		return (-1);
	}
	setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(ft_atoi(port));
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

int server(const char *port)
{
	int lsock;
	struct connected_socket control;
	socklen_t len;
	pid_t pi;
	int ret;

	lsock = create_server(port);
	if (lsock < 0)
		return (1);
	if (signal(SIGCHLD, child_handler) == SIG_ERR)
		return (2);
	while (1) {
		control.sock = accept(lsock, (struct sockaddr *)&(control.addr),
			&len);
		if (control.sock < 0)
			fprintf(stderr, "Error: accept\n");
		pi = fork();
		if (pi < 0) {
			send_reply(client.control.sock, FTP_SYNT_OK);//FTP_CONN_CTRL_ERR);
		} else if (pi == 0) {
			close(lsock);
			ret = protocol_interpreter(control);
			exit(ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
		}
		close(control.sock);
	}
	close(lsock);
	return (0);
}
