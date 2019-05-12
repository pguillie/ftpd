/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:21:26 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/11 11:23:17 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

void die(int control_sock)
{
	send_reply(control_sock, FTP_CONN_CTRL_ERR);
	close(control_sock);
	exit(EXIT_FAILURE);
}
