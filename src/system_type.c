/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:41:08 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/03 20:44:51 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"

int system_type(char *arguments __attribute__((unused)))
{
	send_reply(client.control.sock, FTP_INFO_SYS_TYPE, "UNIX");
	return (0);
}
