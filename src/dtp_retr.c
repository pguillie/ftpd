/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:27:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/05 21:15:35 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"

struct ftp_client client;

int dtp_retr(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (send_data(client.data.sock, fd) < 0)
		return (FTP_CONN_ABORT_ERR);
	return (FTP_CONN_DATA_CLOSE);
}
