/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:56:53 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/20 16:37:43 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

int logout(int control_sock)
{
	send_reply(control_sock, FTP_CONN_CTRL_CLOSE);
	close(control_sock);
	exit(EXIT_SUCCESS);
}
