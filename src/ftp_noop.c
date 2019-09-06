/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_noop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 12:50:28 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/08 12:57:13 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"

int ftp_noop(struct ftp_session *session)
{
	send_reply(session->control.sock, FTP_SYNT_CMD_OK, "NOOP");
	return 0;
}
