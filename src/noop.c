/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 12:50:28 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/23 12:54:07 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"

struct ftp_client client;

int noop(char *arguments __attribute__((unused)))
{
	send_reply(client.control.sock, FTP_SYNT_CMD_OK, "NOOP");
	return (0);
}
