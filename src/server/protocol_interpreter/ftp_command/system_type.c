/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:41:08 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/20 16:37:56 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

int system_type(int control_sock)
{
	send_reply(control_sock, FTP_INFO_SYS_TYPE);
	return (0);
}
