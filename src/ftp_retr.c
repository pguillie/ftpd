/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_retr                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:58:36 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/15 14:41:59 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "protocol_interpreter.h"
#include "data_transfer_process.h"

int ftp_retr(struct ftp_session *session)
{
	if (!session->user.pw_uid) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	if (access(session->args, R_OK) != 0) {
		send_reply(session->control.sock, FTP_FILE_ERR);
		return 1;
	}
	session->command = &dtp_retr;
	send_reply(session->control.sock, FTP_FILE_RETR_OPEN);
	return data_transfer_process(session);
}
