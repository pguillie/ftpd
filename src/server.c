/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 09:09:49 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/27 08:22:22 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

#define LISTEN_BACKLOG (8)

static void child_handler(int sig __attribute__((unused)))
{
	wait4(-1, NULL, 0, NULL);
}

static int use_addr(struct addrinfo addr)
{
	int s;

	do {
		s = socket(addr.ai_family, addr.ai_socktype, addr.ai_protocol);
		if (s == -1)
			break;
		setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
		if (bind(s, addr.ai_addr, addr.ai_addrlen))
			break;
		if (listen(s, LISTEN_BACKLOG) < 0)
			break;
		return s;
	} while (0);
	close(s);
	return -1;
}

static int run_service(struct addrinfo *rp)
{
	int sfd = -1;

	if (rp == NULL)
		return -1;
	if (rp->ai_family == AF_INET6) {
		sfd = use_addr(*rp);
		if (sfd == -1)
			return run_service(rp->ai_next);
	} else {
		sfd = run_service(rp->ai_next);
		if (sfd == -1)
			return use_addr(*rp);
	}
	return sfd;
}

static int create_server(const char *service)
{
	struct addrinfo hints, *result;
	int sfd;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_PASSIVE;
	if (!service)
		service = "ftp";
	if (getaddrinfo(NULL, service, &hints, &result) != 0)
		return -1;
	sfd = run_service(result);
	freeaddrinfo(result);
	return sfd;
}

int server(const char *service)
{
	int lsoc;
	int csoc;
	struct sockaddr_storage peer_addr;
	socklen_t addr_len;
	pid_t session;

	lsoc = create_server(service);
	if (lsoc < 0) {
		fprintf(stderr, "Error: unable to create server\n");
		return 1;
	}
	if (signal(SIGCHLD, child_handler) == SIG_ERR)
		return 2;
	while (1) {
		addr_len = sizeof(struct sockaddr_storage);
		csoc = accept(lsoc, (struct sockaddr *)&peer_addr, &addr_len);
		if (csoc < 0) {
			fprintf(stderr, "Error: accept\n");
			continue ;
		}
		server_log("open connection", (struct sockaddr *)&peer_addr,
			addr_len);
		session = fork();
		if (session < 0) {
			fprintf(stderr, "Error: fork\n");
			send_reply(csoc, FTP_CONN_CTRL_ERR);
		} else if (session == 0) {
			close(lsoc);
			if (session_manager(csoc, peer_addr, addr_len) != 0)
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		close(csoc);
	}
	close(lsoc);
	return 0;
}
