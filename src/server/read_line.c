/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 05:13:33 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/12 13:20:30 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdio.h>

static int copy_line(char *line, size_t size, char *buf, size_t n)
{
	if (n > size - 1)
		return (1);
	memcpy(line, buf, n);
	line[n] = '\0';
	return (0);
}

int read_line(int fd, char *line, size_t size)
{
	static char buf[1024];
	static ssize_t n;
	char *nl;
	size_t i;
	int overflow;

	i = 0;
	overflow = 0;
	while ((nl = memchr(buf, '\n', n)) == NULL) {
		if (!overflow)
			overflow = copy_line(line + i, size - i, buf, n);
		i += n;
		n = read(fd, buf, 1024);
		if (n < 0) {
			n = 0;
			return (-1);
		} else if (n == 0) {
			return (0);
		}
	}
	if (!overflow)
		overflow = copy_line(line + i, size - i, buf, nl - buf - 1); // '\r'
	n = buf + n - (nl + 1);
	memmove(buf, nl + 1, n);
	return (overflow ? 2 : 1);
}
