/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/26 12:41:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

#include <stdio.h> //printf

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
