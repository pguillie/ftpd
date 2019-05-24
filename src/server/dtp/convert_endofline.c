/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_endofline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 10:49:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/24 12:34:21 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

void convert_endofline(int input, int output)
{
	char bufin[1024], bufout[1024];
	ssize_t n;
	size_t i, j;

	j = 0;
	while ((n = read(input, bufin, sizeof(bufin))) > 0) {
		i = 0;
		while (i < (size_t)n) {
			if (bufin[i] == '\n')
				bufout[j++] = '\r';
			bufout[j++] = bufin[i++];
			if (j == sizeof(bufout)) {
				write(output, bufout, j);
				j = 0;
			}
		}
	}
	write(output, bufout, j);
}
