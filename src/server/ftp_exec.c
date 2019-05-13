/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 11:38:21 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/13 07:58:37 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

static struct {
	const char *name;
	int (*f)(int control_soc);
} ftp_command[] = {
	/* {"list", list}, */
	/* {"cwd", change_wdir}, */
	/* {"retr", retrieve}, */
	/* {"stor", store}, */
	{"pwd", print_working_directory},
	/* {"quit", logout} */
	{"user", user_name}
};

int ftp_exec(const char *command, int control_sock)
{
	char code[5];
	size_t i;

	if (command == NULL) {
		send_reply(control_sock, FTP_SYNT_ERR);
		return (1);
	}
	i = 0;
	while (*command && i < 5)
		code[i++] = tolower(*command++);
	if (*command != '\0') {
		send_reply(control_sock, FTP_SYNT_ERR);
		return (1);
	}
	code[i] = '\0';
	i = sizeof(ftp_command) / sizeof(ftp_command[0]);
	while (i--) {
		if (strcmp(ftp_command[i].name, code) == 0)
			return (ftp_command[i].f(control_sock));
	}
	send_reply(control_sock, FTP_SYNT_ERR);
	return (1);
}
