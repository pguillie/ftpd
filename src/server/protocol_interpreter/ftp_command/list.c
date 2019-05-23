/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 11:30:09 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/23 17:05:51 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

int list(char *arguments)
{
	char *path;

	if (!client.user) {
		send_reply(FTP_AUTH_USER_ERR);
		return (1);
	}
	path = strtok(arguments, " ");
	if (strtok(NULL, " ") != NULL) {
		send_reply(FTP_SYNT_ARG_ERR);
		return (1);
	}
	if (path == NULL)
		path = ".";
	if (access(path, F_OK) != 0) {
		send_reply(FTP_FILE_LIST_ERR);
		return (1);
	}
	send_reply(FTP_FILE_DATA_OK);
	data_transfer_process(DTP_LIST, path);
	return (0);
}
