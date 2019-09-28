/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/28 12:58:47 by pguillie         ###   ########.fr       */
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

	name = ft_strtok(session->args, " ");
	if (name == NULL || ft_strtok(NULL, " ") != NULL) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	if (ft_strcmp(name, session->user.pw_name) == 0) {
		send_reply(session->control.sock, FTP_AUTH_OK);
	} else {
		ft_strncpy(session->login, name, sizeof(session->login));
		send_reply(session->control.sock, FTP_AUTH_PASS);
	}
	return 0;
}
