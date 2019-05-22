/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_port.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 10:32:37 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 13:26:34 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/data_transfer_process.h"

struct sockaddr_in client_dtp;

int dtp_port(const char *sockaddr)
{
	write(2, "PORT\n", 5);
	client_dtp = *((struct sockaddr_in *)sockaddr);
	write(1, "200", 3);
	return (0);
}
