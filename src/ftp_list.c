/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 11:30:09 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:25:32 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "protocol_interpreter.h"
#include "data_transfer_process.h"
#include "../libft/include/libft.h"

int ftp_list(struct ftp_session *session)
{
	if (!session->user) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	if (session->args == NULL)
		session->args = ".";
	else if (ft_strchr(session->args, '\n')) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	if (access(session->args, F_OK) != 0) {
		send_reply(session->control.sock, FTP_FILE_LIST_ERR);
		return 1;
	}
	session->command = &dtp_list;
	send_reply(session->control.sock, FTP_FILE_LIST_OPEN);
	return data_transfer_process(session);
}
