/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_auth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 21:08:49 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/24 22:39:23 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__

#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <shadow.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

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
	ftp_log(line, &session->control.addr, session->control.addr_len);
	i = 0;
	while (*str && (line[i++] | 32) == (*str | 32))
		str++;
	if (*str != '\0' || line[i] != ' ') {
		send_reply(session->control.sock, FTP_AUTH_USAGE);
		return NULL;
	}
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

int sys_auth(struct ftp_session *session, const char *login,
	struct passwd **pwd)
{
	struct passwd *pw;
	int success;

	pw = getpwnam(login);
	success = valid_credentials(login, pw, session);
	if (success != 1)
		return 0;
	if (ft_strlen(pw->pw_dir) >= sizeof(session->home))
		return 0;
	ft_strcpy(session->home, pw->pw_dir);
	*pwd = pw;
	return 1;
}

#else  /* __linux__ */

#include "protocol_interpreter.h"

int sys_auth(struct ftp_session *session __attribute__((unused)),
	const char *login __attribute__((unused)),
	struct passwd **pwd __attribute__((unused)))
{
	return 1;
}

#endif	/* __linux__ */
