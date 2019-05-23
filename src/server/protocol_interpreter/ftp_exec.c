/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 11:38:21 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/23 16:55:53 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

static struct {
	const char *name;
	int (*f)(char *arguments);
} ftp_command[] = {
	{"user", user_name},
	{"cwd", change_working_directory},
	{"quit", logout},
	{"port", data_port},
	/* {"retr", retrieve}, */
	/* {"stor", store}, */
	{"pwd", print_working_directory},
	{"list", list},
	{"syst", system_type}
};

int ftp_exec(const char *command, char *arguments)
{
	char code[5];
	size_t i;

	if (command == NULL) {
		send_reply(FTP_SYNT_ERR);
		return (1);
	}
	i = 0;
	while (*command && i < 5)
		code[i++] = tolower(*command++);
	if (*command != '\0') {
		send_reply(FTP_SYNT_ERR);
		return (1);
	}
	code[i] = '\0';
	i = sizeof(ftp_command) / sizeof(ftp_command[0]);
	while (i--) {
		if (strcmp(ftp_command[i].name, code) == 0)
			return (ftp_command[i].f(arguments));
	}
	send_reply(FTP_SYNT_ERR);
	return (1);
}
