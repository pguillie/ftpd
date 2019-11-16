/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chroot_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:48:42 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/22 10:40:11 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

#include "../libft/include/libft.h"

static int resolve_path(const char *path, char *chrooted, size_t *i, size_t l)
{
	if (*path == '/')
		return 1;
	if (*path == '.') {
		if (path[1] == '\0' || path[1] == '/')
			return 1;
		if (path[1] == '.' && (path[2] == '\0' || path[2] == '/')) {
			if (*i > l + 1)
				while (chrooted[--(*i) - 1] != '/') ;
			return 2;
		}
	}
	return 0;
}

static size_t prefix(const char **path, const char *home, char *chrooted)
{
	size_t len;

	if (**path != '/') {
		if (getcwd(chrooted, PATH_MAX - 2) == NULL)
			return 0;
		len = ft_strlen(chrooted);
	} else {
		(*path)++;
		len = ft_strlen(home);
		ft_memcpy(chrooted, home, len);
	}
	chrooted[len++] = '/';
	return len;
}

char *chroot_home(const char *home, const char *path, char *chrooted)
{
	size_t home_len, i, j;

	home_len = ft_strlen(home);
	i = prefix(&path, home, chrooted);
	if (i == 0)
		return NULL;
	while (*path != '\0') {
		j = resolve_path(path, chrooted, &i, home_len);
		if (j == 0) {
			while (path[j] != '\0' && path[j] != '/') {
				if (i > PATH_MAX - 3)
					return NULL;
				chrooted[i++] = path[j++];
			}
			chrooted[i] = '\0';
			if (access(chrooted, F_OK) != 0)
				return NULL;
			chrooted[i++] = '/';
		}
		path += j;
	}
	chrooted[(i < home_len) ? i : i - 1] = '\0';
	return chrooted;
}
