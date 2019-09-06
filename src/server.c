/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 09:09:49 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 08:01:39 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

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
		return -1;
	}
	setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(ft_atoi(port));
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (bind(lsock, (struct sockaddr *)&addr, sizeof(addr))) {
		fprintf(stderr, "Error: bind\n");
		return -1;
	}
	if (listen(lsock, 3) < 0) {
		fprintf(stderr, "Error: listen\n");
		return -1;
	}
	return lsock;
}

int server(const char *port)
{
	int lsock;
	int sock;
	struct sockaddr_in addr;
	socklen_t len;
	pid_t pi;

	lsock = create_server(port);
	if (lsock < 0)
		return 1;
	if (signal(SIGCHLD, child_handler) == SIG_ERR)
		return 2;
	while (1) {
		sock = accept(lsock, (struct sockaddr *)&(addr), &len);
		if (sock < 0) {
			fprintf(stderr, "Error: accept\n");
			continue ;
		}
		pi = fork();
		if (pi < 0) {
			fprintf(stderr, "Error: fork\n");
			send_reply(sock, FTP_CONN_CTRL_ERR);
		} else if (pi == 0) {
			close(lsock);
			if (protocol_interpreter(sock, addr) != 0)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		close(sock);
	}
	close(lsock);
	return 0;
}
