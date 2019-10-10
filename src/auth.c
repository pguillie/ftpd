/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auth.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 11:34:34 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/10 11:19:44 by pguillie         ###   ########.fr       */
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
	char line[128];//
	int ret;

	send_reply(session->control.sock, FTP_AUTH_PASS);
	ret = recv_command(session->control.sock, line, sizeof(line));
	if (ret > 1) {
		send_reply(session->control.sock, FTP_SYNT_TOO_LONG);
		return NULL;
	}
	set_command(session, line);
	if (session->command != &ftp_pass || session->args == NULL) {
		send_reply(session->control.sock, FTP_AUTH_USAGE);
		return NULL;
	}
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
	printf("get login: %s\n", login);
	if (ret == 1) {
		pwd = getpwnam(login);
		spwd = getspnam(login);
		passwd = get_password(session);
		printf("passwd: %s\n", passwd);
		if (pwd != NULL) {
			write(1, "foo\n", 4);
			if (spwd != NULL)
				pwd->pw_passwd = spwd->sp_pwdp;
			else
				perror("shadow");
			encrypted = crypt(passwd, pwd->pw_passwd);
			printf("enc: %s\npwd: %s\n", encrypted, pwd->pw_passwd);
		} else {
			write(1, "bar\n", 4);
			encrypted = NULL;
		}
		write(1, "baz\n", 4);
		ft_memset(passwd, '\0', ft_strlen(passwd));
		free(passwd);
		write(1, "A\n", 2);
		if (encrypted && ft_strcmp(encrypted, pwd->pw_passwd) == 0) {
			*pwd_ptr = pwd;
			send_reply(session->control.sock, FTP_AUTH_OK);
		} else {
			printf("Wrong password\n");
			send_reply(session->control.sock, FTP_AUTH_ERR);
		}
		write(1, "B\n", 2);
	} else if (ret == -1)
		send_reply(session->control.sock, FTP_CONN_CTRL_ERR);
	return ret;
}
