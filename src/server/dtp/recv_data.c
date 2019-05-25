/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:55:38 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/25 13:39:19 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

void recv_data(int fd)
{
	char buf[1024], data[1024];
	ssize_t n;
	size_t i, j;

	i = 0;
	while ((n = read(client.data.sock, data, sizeof(data))) > 0) {
		j = 0;
		while (j < (size_t)n) {
			if (data[j] == '\r') {
				j++;
				continue ;
			}
			buf[i++] = data[j++];
			if (i == sizeof(buf)) {
				write(fd, buf, i);
				i = 0;
			}
		}
	}
	write(fd, buf, i);
}
