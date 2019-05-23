/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:21:26 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/23 16:35:46 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

void die(void)
{
	send_reply(FTP_CONN_CTRL_ERR);
	close(client.control.sock);
	exit(EXIT_FAILURE);
}
