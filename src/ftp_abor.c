/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_abor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 07:46:51 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/23 10:14:12 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <signal.h>

#include "protocol_interpreter.h"
#include "dtp.h"

pid_t dtp;

int ftp_abor(struct ftp_session *session)
{
	if (dtp == -1) {
		send_reply(session->control.sock, FTP_CONN_ABORT_NONE);
		return 0;
	}
	if (kill(dtp, SIGINT) == -1 && kill(dtp, SIGKILL) == -1)
		return -1;
	while (dtp != -1) ;
	send_reply(session->control.sock, FTP_CONN_ABORT_OK);
	return 0;
}
