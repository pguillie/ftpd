/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:55:22 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:20:12 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

int ftp_cwd(struct ftp_session *session)
{
	char *path;

	if (!session->user) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	path = ft_strtok(session->args, " ");
	if (path == NULL || ft_strtok(NULL, " ") != NULL) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	if (chdir(path) < 0) {
		send_reply(session->control.sock, FTP_FILE_CWD_ERR);
		return 1;
	}
	send_reply(session->control.sock, FTP_FILE_CWD_OK);
	return 0;
}
