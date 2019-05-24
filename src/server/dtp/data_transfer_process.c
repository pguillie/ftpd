/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transfer_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:07:39 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/24 11:37:51 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

typedef int (*dtp_function)(const char *file);

dtp_function dtp_command[] = {
	&dtp_list
};

static int connect_data(void)
{
	client.data.sock = socket(AF_INET, SOCK_STREAM, 0);
	if (client.data.sock < 0) {
		perror("Error: dtp socket");
		return (-1);
	}
	if (connect(client.data.sock, (struct sockaddr *)&(client.data.addr),
			sizeof(client.data.addr)) < 0) {
		perror("Error: dtp connect");
		return (-1);
	}
	return (0);
}

pid_t data_transfer_process(enum e_dtp_type id, const char *file)
{
	pid_t dtp;
	int ret;

	dtp = fork();
	if (dtp < 0) {
		fprintf(stderr, "Error: DTP fork\n");
		return (-1);
	} else if (dtp == 0) {
		if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
			exit(2);
		if (connect_data() < 0)
			exit(2);
		ret = dtp_command[id](file);
		exit(ret);
	}
	return (dtp);
}
