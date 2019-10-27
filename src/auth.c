/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 11:34:34 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/27 11:01:00 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <shadow.h>

#include "protocol_interpreter.h"
#include "ftp_command.h"
#include "../libft/include/libft.h"

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

static char *get_password(struct ftp_session *session)
{
	const char *str = "PASS";
	char line[128];
	size_t i;
	int ret;

	send_reply(session->control.sock, FTP_AUTH_PASS);
	ret = recv_command(session->control.sock, line, sizeof(line));
	if (ret > 1) {
		send_reply(session->control.sock, FTP_SYNT_TOO_LONG);
		return NULL;
	}
	i = 0;
	while (*str && (line[i++] | 32) == (*str | 32))
		str++;
	if (*str != '\0' || line[i] != ' ') {
		server_log(line, (struct sockaddr *)&session->control.addr,
		session->control.addr_len);
		send_reply(session->control.sock, FTP_AUTH_USAGE);
		return NULL;
	}
	server_log("PASS ****", (struct sockaddr *)&session->control.addr,
		session->control.addr_len);
	return ft_strdup(line + i + 1);
}

static int valid_credentials(const char *login, struct passwd *pwd,
	struct ftp_session *session)
{
	struct spwd *spwd;
	char *passwd, *encrypted;

	spwd = getspnam(login);
	passwd = get_password(session);
	if (passwd == NULL)
		return -1;
	if (pwd) {
		if (spwd)
			pwd->pw_passwd = spwd->sp_pwdp;
		encrypted = crypt(passwd, pwd->pw_passwd);
	} else {
		encrypted = NULL;
	}
	ft_memset(passwd, '\0', ft_strlen(passwd));
	free(passwd);
	if (!encrypted || ft_strcmp(encrypted, pwd->pw_passwd) != 0)
		return 0;
	return 1;
}

int auth(int pipefd, struct ftp_session *session, struct passwd **pwd_ptr)
{
	struct passwd *pwd;
	char login[256];
	int success;

	*pwd_ptr = NULL;
	success = get_session_login(pipefd, session, login);
	if (success == -1)
		send_reply(session->control.sock, FTP_CONN_CTRL_ERR);
	if (success != 1)
		return -1;
	if (getuid() == 0) {
		pwd = getpwnam(login);
		success = valid_credentials(login, pwd, session);
		if (success == 0)
			send_reply(session->control.sock, FTP_AUTH_ERR);
		if (success != 1)
			return 0;
		*pwd_ptr = pwd;
	}
	send_reply(session->control.sock, FTP_AUTH_OK);
	return 1;
}
