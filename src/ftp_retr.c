/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_retr                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:58:36 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/22 10:49:47 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "protocol_interpreter.h"
#include "data_transfer_process.h"

static int valid_file(const char *file)
{
	struct stat buf;
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return 0;
	if (fstat(fd, &buf) == -1) {
		close(fd);
		return 0;
	}
	if (!S_ISREG(buf.st_mode)) {
		close(fd);
		return 0;
	}
	close(fd);
	return 1;
}

int ftp_retr(struct ftp_session *session)
{
	char path[PATH_MAX];

	if (!session->auth) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	if (chroot_home(session->home, session->args, path) == NULL
		|| !valid_file(path)) {
		send_reply(session->control.sock, FTP_FILE_RETR_ERR);
		return 1;
	}
	session->command = &dtp_retr;
	session->args = path;
	send_reply(session->control.sock, FTP_FILE_RETR_OPEN);
	return data_transfer_process(session);
}
