/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_reply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:46:43 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/23 16:22:10 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

int send_reply(const char *reply)
{
	char buf[128];
	size_t len;

	len = strlen(reply);
	if (len + EOL_LENGTH <= sizeof(buf)) {
		memcpy(buf, reply, len);
		memcpy((char *)buf + len, EOL, EOL_LENGTH);
		if (send(client.control.sock, buf, len + EOL_LENGTH, 0) < 0)
			return (-1);
		return (0);
	}
	// above: if -> while
	return (1);
}
