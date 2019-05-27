/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 08:46:11 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/27 08:46:11 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;

	if (dest < src) {
		i = 0;
		while (i < n) {
			dest[i] = src[i];
			i++;
		}
	} else {
		while (n--)
			dest[n] = src[n];
	}
	return (dest);
}
