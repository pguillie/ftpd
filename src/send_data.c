/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 10:49:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/24 13:40:16 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "data_transfer_process.h"

#define BUFSIZE (1024)

static int flush_data(char *data, int soc, size_t *i)
{
	if (send(soc, data, *i, 0) < 0)
		return -1;
	*i = 0;
	return 0;
}

static int send_data_asc(int soc, int fd)
{
	char buf[BUFSIZE], data[BUFSIZE];
	ssize_t n;
	size_t i, j;

	i = 0;
	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		j = 0;
		while (j < (size_t)n) {
			if (i >= sizeof(data) - 1
				&& flush_data(data, soc, &i) != 0)
				return -1;
			if (buf[j] == '\n')
				data[i++] = '\r';
			data[i++] = buf[j++];
		}
	}
	if (n < 0 || ((i && send(soc, data, i, 0) < 0)))
		return -1;
	return 0;
}

static int send_data_bin(int soc, int fd)
{
	char buf[BUFSIZE];
	ssize_t n;

	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		if (send(soc, buf, n, 0) < 0)
			return -1;
	}
	if (n < 0)
		return -1;
	return 0;
}

int send_data(int soc, int fd, enum ftp_data_type type)
{
	if (type == TYPE_ASCII)
		return send_data_asc(soc, fd);
	else
		return send_data_bin(soc, fd);
}
