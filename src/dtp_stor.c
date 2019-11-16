/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_stor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 13:16:32 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/22 08:03:43 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "data_transfer_process.h"
#include "ftp_reply.h"

int dtp_stor(struct ftp_session *session)
{
	int fd;

	fd = open(session->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return FTP_FILE_LOCAL_ERR;
	if (recv_data(session->data.sock, fd, session->data_type) < 0) {
		close(fd);
		return FTP_CONN_ABORT_ERR;
	}
	close(fd);
	return FTP_CONN_DATA_CLOSE;
}
