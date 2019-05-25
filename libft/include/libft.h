/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 05:05:16 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/25 16:24:14 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

int get_next_line(int fd, char **line);

void *ft_memmem(const void *haystack, size_t haystacklen,
	const void *needle, size_t needlelen);

#endif /* LIBFT_H */
