/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:56:53 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/03 20:49:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"

struct ftp_client client;

int logout(char *arguments __attribute__((unused)))
{
	send_reply(client.control.sock, FTP_CONN_CTRL_CLOSE);
	close(client.control.sock);
	exit(EXIT_SUCCESS);
}
