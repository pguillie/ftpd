/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:20:56 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/22 09:42:55 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

int ftp_pwd(struct ftp_session *session)
{
	char cwd[PATH_MAX], *chroot;

	if (!session->auth) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	if (getcwd(cwd, PATH_MAX) == NULL) {
		send_reply(session->control.sock, FTP_FILE_PWD_ERR);
		return 2;
	}
	chroot = cwd + ft_strlen(session->home);
	send_reply(session->control.sock, FTP_FILE_PWD_OK,
		*chroot ? chroot : "/");
	return 0;
}
