/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:21:35 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/24 13:09:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "protocol_interpreter.h"

static int connection(int csoc, struct sockaddr_storage peer, socklen_t len)
{
	int ret;

	ftp_log("[+] open connection", &peer, len);
	ret = session_manager(csoc, peer, len);
	ftp_log("[-] close connection", &peer, len);
	return ret;
}

int connection_manager(int lsoc)
{
	struct sockaddr_storage peer;
	socklen_t len;
	int csoc, ret;
	pid_t session;

	while (1) {
		len = sizeof(struct sockaddr_storage);
		csoc = accept(lsoc, (struct sockaddr *)&peer, &len);
		if (csoc == -1) {
			fprintf(stderr, "Error: accept\n");
			continue;
		}
		session = fork();
		if (session < 0) {
			fprintf(stderr, "Error: fork\n");
			send_reply(csoc, FTP_CONN_CTRL_ERR);
			return -1;
		} else if (session == 0) {
			close(lsoc);
			ret = connection(csoc, peer, len);
			exit((ret == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
		}
		close(csoc);
	}
	return 0;
}
