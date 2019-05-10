/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 09:09:49 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/10 17:16:22 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

static int create_server(const char *port)
{
	int lsoc;
	struct sockaddr_in addr;

	lsoc = socket(AF_INET, SOCK_STREAM, 0);
	if (lsoc < 0) {
		fprintf(stderr, "Error: socket\n");
		return (-1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port)); // atoi
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if (bind(lsoc, (struct sockaddr *)&addr, sizeof(addr))) {
		fprintf(stderr, "Error: bind\n");
		return (-1);
	}
	if (listen(lsoc, 3) < 0) {
		fprintf(stderr, "Error: listen\n");
		return (-1);
	}
	return (lsoc);
}

static void chld_handler(int sig __attribute__((unused)))
{
	wait4(-1, NULL, 0, NULL);
}

int server(const char *port)
{
	int lsoc, ctrl;
	struct sockaddr_in addr;
	socklen_t len;
	pid_t pi;

	lsoc = create_server(port);
	if (lsoc < 0)
		return (1);
	if (signal(SIGCHLD, chld_handler) == SIG_ERR)
		return (2);
	while (1) {
		ctrl = accept(lsoc, (struct sockaddr *)&addr, &len);
		if (ctrl < 0)
			fprintf(stderr, "Error: accept\n");
		pi = fork();
		if (pi == 0) {
			close(lsoc);
			protocol_interpreter(ctrl);
		} else {
			if (pi < 0)
				reply(ctrl, REP_SHUT_DOWN);
			close(ctrl);
		}
	}
	close(lsoc);
	return (0);
}
