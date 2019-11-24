/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 11:34:34 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/24 16:01:34 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pwd.h>

#include "protocol_interpreter.h"

static int get_session_login(int fd, struct ftp_session *session, char *login)
{
	ssize_t n;

	n = read(fd, session, sizeof(struct ftp_session));
	if (n == 0)
		return 0;
	else if (n < 0 || (size_t)n < sizeof(struct ftp_session))
		return -1;
	n = read(fd, login, sizeof(login));
	if (n < 1)
		return -1;
	login[n] = '\0';
	return 1;
}

int auth(int pipefd, struct ftp_session *session, struct passwd **pwd)
{
	char login[256];
	int success;

	*pwd = NULL;
	success = get_session_login(pipefd, session, login);
	if (success == -1)
		send_reply(session->control.sock, FTP_CONN_CTRL_ERR);
	if (success != 1)
		return -1;
	if (getuid() == 0 && sys_auth(session, login, pwd) != 1) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 0;
	}
	send_reply(session->control.sock, FTP_AUTH_OK);
	return 1;
}
