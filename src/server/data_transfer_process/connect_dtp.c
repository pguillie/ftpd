/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_dtp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:49:37 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 12:10:03 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/data_transfer_process.h"

struct sockaddr_in client_dtp;

int connect_dtp(void)
{
	int data_sock;

	write(1, "150", 3);
	data_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (data_sock < 0) {
		perror("Error: DTP socket");
		return (-1);
	}
	if (connect(data_sock, (struct sockaddr *)&(client_dtp),
			sizeof(client_dtp)) < 0) {
		perror("Error: DTP connect");
		return (-1);
	}
//	fprintf(stderr, "%s:%d\n", inet_ntoa(client_dtp.sin_addr), ntohs(client_dtp.sin_port));
	return (data_sock);
}
