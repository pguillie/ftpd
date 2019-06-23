/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:51:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/23 13:59:39 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

//
struct ftp_client client;
//
pid_t dtp = -1;

static void dtp_exit_status(int sig __attribute__((unused)))
{
	int ftp_reply_code;

	wait4(dtp, &ftp_reply_code, 0, NULL);
	dtp = -1;
	if (WIFEXITED(ftp_reply_code))
		send_reply(client.control.sock, WEXITSTATUS(ftp_reply_code));
	else
		send_reply(client.control.sock, FTP_FILE_LOCAL_ERR);
}

int protocol_interpreter(struct connected_socket control)
{
	char line[128];
	char *command, *arguments;
	int ret;

	client.user = NULL;
	client.control = control;
	client.data.addr = control.addr;
	client.binary = 0;
	if (signal(SIGCHLD, dtp_exit_status) == SIG_ERR)
		return (2);
	send_reply(client.control.sock, FTP_CONN_CTRL_READY);
	while ((ret = recv_command(client.control.sock, line, sizeof(line))) > 0) {
		if (ret > 1) {
			send_reply(client.control.sock, FTP_SYNT_TOO_LONG);
			continue ;
		}
		printf("[%s]\n", line); //
		command = strtok(line, " ");
		arguments = strtok(NULL, "\0");
		if (execute(command, arguments) < 0)
			die();
	}
	close(client.control.sock); //whole client data?
	return (ret < 0 ? 1 : 0);
}
