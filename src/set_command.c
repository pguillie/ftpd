/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 08:50:57 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/26 08:17:59 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_command.h"
#include "../libft/include/libft.h"

static struct {
	const char *name;
	int (*fptr)(struct ftp_session *session);
} command[] = {
	{"user", &ftp_user},
	{"cwd", &ftp_cwd},
	{"quit", &ftp_quit},
	{"port", &ftp_port},
	{"type", &ftp_type},
	{"retr", &ftp_retr},
	{"stor", &ftp_stor},
	{"pwd", &ftp_pwd},
	{"list", &ftp_list},
	{"syst", &ftp_syst},
	{"noop", &ftp_noop},
	{"eprt", &ftp_eprt}
};

int set_command(struct ftp_session *session, char *cmd_line)
{
	char *cmd;
	size_t i;

	cmd = ft_strtok(cmd_line, " ");
	if (cmd == NULL)
		return 1;
	i = 0;
	while (cmd[i]) {
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	i = sizeof(command) / sizeof(command[0]);
	while (i--) {
		if (ft_strcmp(command[i].name, cmd) == 0) {
			session->command = command[i].fptr;
			session->args = ft_strtok(NULL, "\0");
			return 0;
		}
	}
	return 1;
}
