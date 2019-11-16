/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_stor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 13:12:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/22 07:53:24 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "protocol_interpreter.h"
#include "data_transfer_process.h"
#include "../libft/include/libft.h"

static int valid_dir(struct ftp_session *session, char *buf)
{
	char *file;
	size_t len, i;

	i = 0;
	file = session->args;
	while (session->args[i])
		if (session->args[i++] == '/')
			file = session->args + i;
	if (*file == '\0')
		return 0;
	else if (file == session->args)
		session->args = ".";
	else
		file[-1] = '\0';
	if (chroot_home(session->home, session->args, buf) == NULL)
		return 0;
	len = ft_strlen(buf);
	if (buf[len - 1] != '/')
		buf[len++] = '/';
	if (len + ft_strlen(file) + 1 >= PATH_MAX)
		return 0;
	ft_strcpy(buf + len, file);
	return 1;
}

static int valid_file(const char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return 0;
	close(fd);
	return 1;
}

int ftp_stor(struct ftp_session *session)
{
	char path[PATH_MAX];

	if (!session->auth) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	if (!valid_dir(session, path)
		|| !valid_file(path)) {
		send_reply(session->control.sock, FTP_FILE_STOR_ERR);
		return 1;
	}
	session->command = &dtp_stor;
	session->args = path;
	send_reply(session->control.sock, FTP_FILE_STOR_OPEN);
	return data_transfer_process(session);
}
