/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 13:12:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/05 21:36:58 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"

struct ftp_client client;

int store(char *file)
{
	if (!client.user) {
		send_reply(client.control.sock, FTP_AUTH_ERR);
		return (1);
	}
	/* if (access(file, R_OK) != 0) { */
	/* 	send_reply(client.control.sock, FTP_FILE_ERR); */
	/* 	return (1); */
	/* } */
	send_reply(client.control.sock, FTP_FILE_STOR_OPEN);
	return (data_transfer_process(DTP_STOR, file));
}
