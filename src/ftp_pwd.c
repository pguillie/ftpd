/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:20:56 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 09:27:10 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

#include "protocol_interpreter.h"

int ftp_pwd(struct ftp_session *session)
{
	char cwd[PATH_MAX];

	if (!session->user) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	if (getcwd(cwd, PATH_MAX) == NULL) {
		send_reply(session->control.sock, FTP_FILE_PWD_ERR);
		return 2;
	}
	send_reply(session->control.sock, FTP_FILE_PWD_OK, cwd);
	return 0;
}
