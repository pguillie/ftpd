/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 11:34:34 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/05 13:37:17 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <shadow.h>

#include "protocol_interpreter.h"
#include "ftp_command.h"
#include "../libft/include/libft.h"

#include <stdio.h> //printf

static char *get_password(struct ftp_session *session)
{
	char line[128];//
	int ret;

	send_reply(session->control.sock, FTP_AUTH_PASS);
	ret = recv_command(session->control.sock, line, sizeof(line));
	if (ret > 1) {
		send_reply(session->control.sock, FTP_SYNT_TOO_LONG);
		return NULL;
	}
	set_command(session, line);
	if (session->command == &ftp_pass && session->args != NULL)
		return NULL;
	send_reply(session->control.sock, FTP_AUTH_USAGE);
	return ft_strdup(session->args);
}

int auth(int pipefd, struct ftp_session *session, struct passwd **pwd_ptr)
{
	struct passwd *pwd;
	struct spwd *spwd;
	char login[256];
	char *passwd, *encrypted;
	int ret;

	*pwd_ptr = NULL;
	ret = get_session_login(pipefd, session, login);
	if (ret == 1) {
		printf("get login: %s\n", login);
		passwd = get_password(session);
		printf("passwd: %s\n", passwd);
		pwd = getpwnam(login);
		spwd = getspnam(login);
		if (pwd == NULL || spwd == NULL) {
			printf("NULL struct!\n");
			ft_memset(passwd, '\0', ft_strlen(passwd));
			free(passwd);
			return ret;
		}
		if (spwd != NULL)
			pwd->pw_passwd = spwd->sp_pwdp;
		encrypted = crypt(passwd, pwd->pw_passwd);
		ft_memset(passwd, '\0', ft_strlen(passwd));
		free(passwd);
		if (ft_strcmp(encrypted, pwd->pw_passwd) == 0)
			*pwd_ptr = pwd;
		else
			printf("Wrong password?\n");
	}
	return ret;
}
