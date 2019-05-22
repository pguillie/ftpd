/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transfer_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:16:16 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 10:29:35 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/data_transfer_process.h"

struct sockaddr_in client_dtp;
pid_t pi;
int abort_data_transfer = 0;

static void term_handler(int sig)
{
	psignal(sig, "DTP");
	kill(pi, sig);
	exit(EXIT_FAILURE);
}

/* static void update_client_dtp_addr(int sig __attribute__((unused))) */
/* { */
/* 	size_t i, n; */
/* 	ssize_t bytes; */

/* 	write(2, "READ PORT\n", 10); */
/* 	n = sizeof(client_dtp); */
/* 	i = 0; */
/* 	while (i < n) { */
/* 		bytes = read(0, (char *)&client_dtp + i, n - i); */
/* 		if (bytes < 0) { */
/* 			write(2, "FUCK\n", 5); */
/* 			raise(SIGTERM); */
/* 		} */
/* 		i += bytes; */
/* 	} */
/* 	/\* ssize_t n; *\/ */
/* 	/\* write(2, "bar\n", 4); *\/ */
/* 	/\* n = read(0, &client_dtp, sizeof(client_dtp)); *\/ */
/* 	/\* fprintf(stderr, "read: %lu / %lu\n", n, sizeof(client_dtp)); *\/ */
/* 	write(2, &client_dtp, sizeof(client_dtp)); */
/* 	/\* if (n < (ssize_t)sizeof(client_dtp)) { *\/ */
/* 	/\* 	write(2, "FOO\n", 4); *\/ */
/* 	/\* 	raise(SIGTERM); *\/ */
/* 	/\* } *\/ */
/* } */

static void abort_transfer(int sig __attribute__((unused)))
{
	abort_data_transfer = 1;
}

static int handle_terminaison_signals(void)
{
	if (signal(SIGTERM, term_handler) == SIG_ERR)
		return (-1);
	if (signal(SIGINT, term_handler) == SIG_ERR)
		return (-1);
	if (signal(SIGQUIT, term_handler) == SIG_ERR)
		return (-1);
	/* if (signal(SIGUSR1, update_client_dtp_addr) == SIG_ERR) */
	/* 	return (-1); */
	if (signal(SIGUSR1, abort_transfer) == SIG_ERR)
		return (-1);
	return (0);
}

static char *read_transfer_command(void)
{
	char *command;
	uint16_t command_sz;

	if (read(0, &command_sz, 2) < 2)
		return (NULL);
	command = malloc(command_sz);
	if (command == NULL)
		return (NULL);
	if (read(0, command, command_sz) < command_sz) {
		free(command);
		return (NULL);
	}
	return (command);
}

void data_transfer_process(void)
{
	char *transfer;

	pi = getppid();
	if (handle_terminaison_signals() < 0)
		kill(pi, SIGTERM);
	while ((transfer = read_transfer_command())) {
		transfer_function(transfer);
		free(transfer);
	}
	raise(SIGTERM);
}
