/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:51:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/13 06:11:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

void protocol_interpreter(int control_sock)
{
	char line[128];
	char *command;
	int ret;

	send_reply(control_sock, FTP_CONN_CTRL_READY);
	while ((ret = read_line(control_sock, line, sizeof(line))) > 0) {
		if (ret > 1) {
			send_reply(control_sock, FTP_SYNT_TOO_LONG);
			continue ;
		}
		printf("[%s]\n", line); //
		command = strtok(line, " ");
		if (ftp_exec(command, control_sock) < 0)
			die(control_sock);
	}
	close(control_sock);
	exit(ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
