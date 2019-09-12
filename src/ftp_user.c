/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 10:52:05 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <unistd.h>
#include <grp.h>

#include <stdio.h> //perror

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

int ftp_user(struct ftp_session *session)
{
	char *name;
	struct passwd *pw;

	session->user = NULL;
	name = ft_strtok(session->args, " ");
	if (name == NULL || ft_strtok(NULL, " ") != NULL) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	pw = getpwnam(name);
	if (pw == NULL || pw->pw_uid == 0) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	if (setgid(pw->pw_gid) < 0
		|| initgroups(pw->pw_name, pw->pw_gid) < 0
		|| setuid(pw->pw_uid) < 0
		|| chdir(pw->pw_dir) < 0)
		die(session);
	session->user = pw;
	send_reply(session->control.sock, FTP_AUTH_OK);
	return 0;
}
