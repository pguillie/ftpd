/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_reply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:46:43 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/12 15:16:05 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

int send_reply(int control_sock, const char *reply)
{
	char buf[128];
	size_t len;

	len = strlen(reply);
	if (len + EOL_LENGTH <= sizeof(buf)) {
		memcpy(buf, reply, len);
		memcpy((char *)buf + len, EOL, EOL_LENGTH);
		if (send(control_sock, buf, len + EOL_LENGTH, 0) < 0)
			return (-1);
		return (0);
	}
	// above: if -> while
	return (1);
}
