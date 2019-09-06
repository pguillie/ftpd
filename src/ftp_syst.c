/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_syst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:41:08 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/08 12:57:05 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"

int ftp_syst(struct ftp_session *session)
{
	send_reply(session->control.sock, FTP_INFO_SYS_TYPE, "UNIX");
	return 0;
}
