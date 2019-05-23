/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transfer_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:07:39 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/23 17:09:35 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;
pid_t dtp;

typedef int (*dtp_function)(int data_sock, const char *file);

dtp_function dtp_command[DTP_TYPE_NUMBER] = {
	dtp_list
};

int data_transfer_process(enum e_dtp_type id, const char *file)
{
	int data_sock;

	dtp = fork();
	if (dtp < 0) {
		fprintf(stderr, "Error: fork DTP\n");
		return (2);
	} else if (dtp == 0) {
		data_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (data_sock < 0)
			perror("Error: DTP socket");
		else if (connect(data_sock, (struct sockaddr *)&(client.data.addr),
				sizeof(client.data.addr)) < 0)
			perror("Error: DTP connect");
		else
			exit(dtp_command[id](data_sock, file));
		exit(1);
	}
	return (0);
}
