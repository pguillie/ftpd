/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 16:03:37 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/25 16:26:39 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmem(const void *haystack, size_t haystacklen,
	const void *needle, size_t needlelen)
{
	size_t i;

	if (haystack == NULL || needle == NULL)
		return ((void *)haystack);
	i = 0;
	while (i < haystacklen) {
		if (memcmp(haystack + i, needle, needlelen) == 0)
			return ((void *)haystack + i);
		i++;
	}
	return (NULL);
}
