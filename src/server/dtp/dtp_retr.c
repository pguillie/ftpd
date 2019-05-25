/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:27:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/25 12:32:11 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

int dtp_retr(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	send_data(fd);
	return (0);
}
