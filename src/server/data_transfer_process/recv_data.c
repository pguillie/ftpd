/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:55:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/23 14:35:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

static int recv_data_bin(int data_sock, int fd)
{
	char buf[1024];
	ssize_t n;

	while ((n = recv(data_sock, buf, sizeof(buf), MSG_NOSIGNAL)) > 0) {
		if (write(fd, buf, n) < 0)
			return (-1);
	}
	if (n < 0)
		return (-1);
	return (0);
}

static int recv_data_asc(int data_sock, int fd)
{
	char buf[1024], data[1024];
	ssize_t n;
	size_t i, j;
	int cr;

	cr = 0;
	i = 0;
	while ((n = recv(data_sock, data, sizeof(data), MSG_NOSIGNAL)) > 0) {
		j = 0;
		while (j < (size_t)n) {
			buf[(cr && data[j] != '\n' ? ++i : i)] = data[j];
			if (data[j++] == '\r') {
				cr = 1;
			} else {
				i++;
				cr = 0;
			}
			if (i == sizeof(buf)) {
				if (write(fd, buf, i) < 0)
					return (-1);
				i = 0;
			}
		}
	}
	if (n < 0 || (i && write(fd, buf, i) < 0))
		return (-1);
	return (0);
}

int recv_data(int data_sock, int fd)
{
	if (client.binary)
		return (recv_data_bin(data_sock, fd));
	else
		return (recv_data_asc(data_sock, fd));
}
