/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:51:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/27 08:22:19 by paul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

static void dtp_exit_status(int sig __attribute__((unused)))
{
	int ret;

	wait4(-1, &ret, 0, NULL);
	if (WIFEXITED(ret)) {
		if (WEXITSTATUS(ret) == 0)
			send_reply(FTP_CONN_DATA_CLOSE);
		else
			send_reply("400 DTP ERROR");
	} else {
		send_reply("500 DTP ERROR");
	}
}

int protocol_interpreter(struct connected_socket control)
{
	char line[128];
	char *command, *arguments;
	int ret;

	client.user = NULL;
	client.control = control;
	client.data.addr = control.addr;
	if (signal(SIGCHLD, dtp_exit_status) == SIG_ERR)
		return (2);
	send_reply(FTP_CONN_CTRL_READY);
	while ((ret = recv_command(line, sizeof(line))) > 0) {
		if (ret > 1) {
			send_reply(FTP_SYNT_TOO_LONG);
			continue ;
		}
		printf("[%s]\n", line); //
		command = strtok(line, " ");
		arguments = strtok(NULL, "\0");
		if (ftp_exec(command, arguments) < 0)
			die();
	}
	close(client.control.sock); //whole client data?
	return (ret < 0 ? 1 : 0);
}
