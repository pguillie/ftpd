/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/04 14:11:21 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

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
	n = sizeof(*session);
	if (write(session->pipefd, session, n) < n)
		exit(EXIT_FAILURE);
	n = ft_strlen(name);
	if (write(session->pipefd, name, n) < n)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
