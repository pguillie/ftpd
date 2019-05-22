/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_dtp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:51:18 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 12:10:54 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/data_transfer_process.h"

pid_t pi;

void close_dtp(int data_sock)
{
	close(data_sock);
	kill(pi, SIGUSR1);
}
