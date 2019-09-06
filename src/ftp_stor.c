/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_stor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 13:12:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/11 10:24:08 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"
#include "data_transfer_process.h"

int ftp_stor(struct ftp_session *session)
{
	if (!session->user) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	/* if (access(session->args, R_OK) != 0) { */
	/* 	send_reply(session->control.sock, FTP_FILE_ERR); */
	/* 	return 1; */
	/* } */
	session->command = &dtp_stor;
	send_reply(session->control.sock, FTP_FILE_STOR_OPEN);
	return data_transfer_process(session);
}
