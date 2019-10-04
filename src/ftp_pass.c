/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_pass.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 08:38:36 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/04 14:16:43 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* PASS is only handled after USER */

#include "protocol_interpreter.h"

int ftp_pass(struct ftp_session *session)
{
	send_reply(session->control.sock, FTP_SYNT_BAD_SEQ);
	return 1;
}
