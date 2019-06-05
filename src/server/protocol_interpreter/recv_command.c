/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 05:13:33 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/04 11:56:19 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

static int copy_line(char *line, size_t size, char *buf, size_t n)
{
	if (n > size - 1)
		return (1);
	memcpy(line, buf, n);
	line[n] = '\0';
	return (0);
}

int recv_command(int control_sock, char *line, size_t size)
{
	static char buf[1024];
	static ssize_t n;
	char *nl;
	size_t i;
	int overflow;

	i = 0;
	overflow = 0;
	while ((nl = (char *)ft_memmem(buf, n, "\r\n", 2)) == NULL) {
		if (!overflow)
			overflow = copy_line(line + i, size - i, buf, n);
		i += n;
		n = read(control_sock, buf, sizeof(buf));
		if (n < 0) {
			n = 0;
			return (-1);
		} else if (n == 0) {
			return (0);
		}
	}
	if (!overflow)
		overflow = copy_line(line + i, size - i, buf, nl - buf);
	n = buf + n - (nl + 2);
	memmove(buf, nl + 2, n);
	return (overflow ? 2 : 1);
}
