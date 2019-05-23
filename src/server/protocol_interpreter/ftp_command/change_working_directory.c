/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_working_directory.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:55:22 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/23 16:58:32 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

int change_working_directory(char *arguments)
{
	char *path;

	if (!client.user) {
		send_reply(FTP_AUTH_USER_ERR);
		return (1);
	}
	path = strtok(arguments, " ");
	if (path == NULL || strtok(NULL, " ") != NULL) {
		send_reply(FTP_SYNT_ARG_ERR);
		return (1);
	}
	if (chdir(path) < 0) {
		send_reply(FTP_FILE_CWD_ERR);
		return (1);
	}
	send_reply(FTP_FILE_CWD_OK);
	return (0);
}
