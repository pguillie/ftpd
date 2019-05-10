/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:46:43 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/10 17:14:47 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

int reply(int ctrl, const char *str)
{
	if (write(ctrl, str, strlen(str)) < 0)
		return (-1);
	if (write(ctrl, EOL, strlen(EOL)) < 0)
		return (-1);
	return (0);
}
