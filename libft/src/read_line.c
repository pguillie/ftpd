/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 19:32:32 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/27 08:46:34 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char *ft_strnapp(char **str, char *to_add, size_t n)
{
	char *res;
	size_t len;

	len = (*str ? ft_strlen(*str) : 0);
	if ((res = (char *)malloc(len + n + 1)) == NULL)
		return (NULL);
	res[len + n] = '\0';
	while (n--)
		res[len + n] = to_add[n];
	while (len--)
		res[len] = (*str)[len];
	free(*str);
	*str = res;
	return (res);
}

static int read_line_return(char **line, char **s, char *nl)
{
	if (nl != NULL) {
		if ((*line = ft_strndup(*s, (size_t)nl - (size_t)*s)) == NULL)
			return (-1);
		ft_memmove(*s, nl + 1, ft_strlen(nl));
		return (1);
	}
	if (*s && (*s)[0]) {
		if ((*line = ft_strdup(*s)) == NULL)
			return (-1);
		free(*s);
		*s = NULL;
		return (1);
	}
	return (0);
}

int read_line(int fd, char **line)
{
	static char *s;
	char buf[1024];
	char *nl;
	ssize_t c;

	if (!line || fd < 0)
		return (-1);
	c = sizeof(buf);
	while ((!s || (nl = ft_strchr(s, '\n')) == NULL) && c == sizeof(buf)) {
		ft_memset(buf, 0, sizeof(buf));
		if ((c = read(fd, buf, sizeof(buf))) > 0)
			if (ft_strnapp(&s, buf, c) == NULL)
				return (-1);
	}
	if (c < 0)
		return (-1);
	return (read_line_return(line, &s, nl));
}
