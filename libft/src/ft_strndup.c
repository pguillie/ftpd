/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 08:46:28 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/27 08:46:28 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
	char *dup;
	size_t l;

	l = ft_strlen(s);
	if (l < n)
		n = l;
	dup = malloc(n);
	if (dup != NULL) {
		ft_memcpy(dup, s, n);
		dup[n] = '\0';
	}
	return (dup);
}
