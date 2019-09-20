/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/20 17:22:27 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

#include <stdio.h>

int ftp_user(struct ftp_session *session)
{
	char *name;
	struct passwd *res;

	ft_memset(&(session->user.pw_uid), 0, sizeof(session->user));
	name = ft_strtok(session->args, " ");
	if (name == NULL || ft_strtok(NULL, " ") != NULL) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	getpwnam_r(name, &(session->user), session->user_buf,
		sizeof(session->user_buf), &res);
	if (res == NULL || res->pw_uid == 0) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	} else if (res->pw_uid == getuid()) {
		send_reply(session->control.sock, FTP_AUTH_OK);
		return 0;
	}
	printf("set user to %s\n", session->user.pw_name);
	if (write(session->pipefd, session, sizeof(*session))
		== sizeof(*session))
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}

/* int ftp_user(struct ftp_session *session) */
/* { */
/* 	char *name; */
/* 	struct passwd *pw; */

/* 	session->user = NULL; */
/* 	name = ft_strtok(session->args, " "); */
/* 	if (name == NULL || ft_strtok(NULL, " ") != NULL) { */
/* 		send_reply(session->control.sock, FTP_SYNT_ERR); */
/* 		return 1; */
/* 	} */
/* 	pw = getpwnam(name); */
/* 	if (pw == NULL || pw->pw_uid == 0) { */
/* 		send_reply(session->control.sock, FTP_AUTH_ERR); */
/* 		return 1; */
/* 	} */
/* 	if (setgid(pw->pw_gid) < 0 */
/* 		|| initgroups(pw->pw_name, pw->pw_gid) < 0 */
/* 		|| setuid(pw->pw_uid) < 0) { */
/* 		session->user = NULL; */
/* 		send_reply(session->control.sock, FTP_AUTH_ERR); */
/* 		return 1; */
/* 	} */
/* 	if (chdir(pw->pw_dir) < 0) */
/* 		die(session); */
/* 	session->user = pw; */
/* 	send_reply(session->control.sock, FTP_AUTH_OK); */
/* 	return 0; */
/* } */
