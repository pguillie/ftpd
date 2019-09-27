/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_dtp_reply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 11:54:23 by marvin            #+#    #+#             */
/*   Updated: 2019/09/27 12:02:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"

void send_dtp_reply(int sock, enum ftp_reply_code rep_idx)
{
	static int _sock;

	if (sock >= 0)
		_sock = sock;
	send_reply(_sock, rep_idx);
}
