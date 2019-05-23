/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:41:08 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/23 16:52:49 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

int system_type(char *arguments __attribute__((unused)))
{
	send_reply(FTP_INFO_SYS_TYPE);
	return (0);
}
