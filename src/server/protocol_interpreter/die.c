/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:21:26 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/04 11:59:36 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

void die(void)
{
	send_reply(client.control.sock, FTP_CONN_CTRL_ERR);
	close(client.control.sock);
	exit(EXIT_FAILURE);
}
