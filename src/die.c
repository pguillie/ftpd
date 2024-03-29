/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:21:26 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:15:13 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "protocol_interpreter.h"

void die(struct ftp_session *session)
{
	send_reply(session->control.sock, FTP_CONN_CTRL_ERR);
	close_session(session);
	exit(EXIT_FAILURE);
}
