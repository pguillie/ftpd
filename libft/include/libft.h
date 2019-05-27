/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 05:05:16 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/27 08:45:35 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include "libfts.h"

int read_line(int fd, char **line);

void *ft_memmem(const void *haystack, size_t haystacklen,
	const void *needle, size_t needlelen);

char *ft_strndup(const char *s, size_t n);
void *ft_memmove(void *dest, const void *src, size_t n);

int ft_atoi(const char *nptr);

#endif /* LIBFT_H */
