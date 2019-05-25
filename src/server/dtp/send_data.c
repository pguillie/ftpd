/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 10:49:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/25 11:27:22 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

void send_data(int fd)
{
	char buf[1024], data[1024];
	ssize_t n;
	size_t i, j;

	i = 0;
	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		j = 0;
		while (j < (size_t)n) {
			if (buf[j] == '\n')
				data[i++] = '\r';
			data[i++] = buf[j++];
			if (i == sizeof(data)) {
				write(client.data.sock, data, i);
				i = 0;
			}
		}
	}
	write(client.data.sock, data, i);
}
