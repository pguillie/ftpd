/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 10:49:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/05 20:55:28 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

int send_data(int data_sock, int fd)
{
	char buf[1024], data[1024];
	ssize_t n;
	size_t i, j;
	int cr;

	cr = 0;
	i = 0;
	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		j = 0;
		while (j < (size_t)n) {
			if (buf[j] == '\n' && !cr) {
				data[i++] = '\r';
				cr = 1;
			} else {
				data[i++] = buf[j++];
				cr = 0;
			}
			if (i == sizeof(data)) {
				if (send(data_sock, data, i, MSG_NOSIGNAL) < 0)
					return (-1);
				i = 0;
			}
		}
	}
	if (n < 0)
		return (-1);
	if (i && send(data_sock, data, i, MSG_NOSIGNAL) < 0)
		return (-1);
	return (0);
}
