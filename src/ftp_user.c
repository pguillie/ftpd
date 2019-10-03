/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/03 12:23:52 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
//#include <pwd.h>
//#include <grp.h>

#include "protocol_interpreter.h"
#include "dtp.h"
#include "../libft/include/libft.h"

int ftp_user(struct ftp_session *session)
{
	char *name;
	ssize_t n;

	name = ft_strtok(session->args, " ");
	if (name == NULL || ft_strtok(NULL, " ") != NULL) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	if (dtp != -1) {
		send_reply(session->control.sock, FTP_AUTH_TRANSFR_ERR);
		return 1;
	}
	ft_strncpy(session->user.login, name, session->lnmax);
//	send_reply(session->control.sock, FTP_AUTH_PASS);
	n = write(session->pipefd, session, sizeof(*session));
	close(
	exit(n == sizeof(*session) ? EXIT_SUCCESS : EXIT_FAILURE);
	return 0;
}
