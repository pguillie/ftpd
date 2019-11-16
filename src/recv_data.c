/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:55:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/16 11:43:09 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "data_transfer_process.h"

#define BUFSIZE (1024)

static int flush_buf(char *buf, int fd, size_t *i)
{
	if (buf[*i - 1] == '\r') {
		if (write(fd, buf, *i - 1) < 0)
			return -1;
		buf[0] = '\r';
		*i = 1;
	} else {
		if (write(fd, buf, *i) < 0)
			return -1;
		*i = 0;
	}
	return 0;
}

static int recv_data_asc(int soc, int fd)
{
	char buf[BUFSIZE], data[BUFSIZE];
	ssize_t n;
	size_t i, j;

	i = 0;
	while ((n = recv(soc, data, sizeof(data), MSG_NOSIGNAL)) > 0) {
		j = 0;
		while (j < (size_t)n) {
			if (data[j] == '\n' && i && buf[i - 1] == '\r')
				i -= 1;
			buf[i++] = data[j++];
			if (i == sizeof(buf) && flush_buf(buf, fd, &i) != 0)
				return -1;
		}
	}
	if (n < 0 || (i && write(fd, buf, i) < 0))
		return -1;
	return 0;
}

static int recv_data_bin(int soc, int fd)
{
	char buf[BUFSIZE];
	ssize_t n;

	while ((n = recv(soc, buf, sizeof(buf), MSG_NOSIGNAL)) > 0) {
		if (write(fd, buf, n) < 0)
			return -1;
	}
	if (n < 0)
		return -1;
	return 0;
}

int recv_data(int soc, int fd, enum ftp_data_type type)
{
	if (type == TYPE_ASCII)
		return recv_data_asc(soc, fd);
	else
		return recv_data_bin(soc, fd);
}
