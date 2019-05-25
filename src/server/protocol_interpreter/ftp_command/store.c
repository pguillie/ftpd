/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 13:12:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/25 13:26:21 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;
pid_t dtp;

int store(char *arguments)
{
	char *file;

	if (!client.user) {
		send_reply(FTP_AUTH_USER_ERR);
		return (1);
	}
	file = strtok(arguments, " ");
	if (file == NULL || strtok(NULL, " ") != NULL) {
		send_reply(FTP_SYNT_ARG_ERR);
		return (1);
	}
	/* if (access(file, R_OK) != 0) { */
	/* 	send_reply(FTP_FILE_ERR); */
	/* 	return (1); */
	/* } */
	send_reply(FTP_FILE_STOR_START);
	dtp = data_transfer_process(DTP_STOR, file);
	return (0);
}
