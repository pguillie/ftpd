/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:56:53 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:20:43 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "protocol_interpreter.h"

int ftp_quit(struct ftp_session *session)
{
	send_reply(session->control.sock, FTP_CONN_CTRL_CLOSE);
	close_session(session);
	exit(EXIT_SUCCESS);
}
