/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:27:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:28:14 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "data_transfer_process.h"
#include "ftp_reply.h"

int dtp_retr(struct ftp_session *session)
{
	int fd;

	fd = open(session->args, O_RDONLY);
	if (fd < 0)
		return 1;
	if (send_data(session->data.sock, fd, session->data_type) < 0)
		return FTP_CONN_ABORT_ERR;
	return FTP_CONN_DATA_CLOSE;
}
