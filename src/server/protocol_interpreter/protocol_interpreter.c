/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:51:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 11:02:54 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

int control_sock;

static void term_handler(int sig)
{
	psignal(sig, "ftpd");
	//die(control_sock); //global access
	exit(EXIT_FAILURE);
}

static void close_data_transfer(int sig)
{
	if (sig == SIGUSR1)
		send_reply(control_sock, FTP_CONN_DATA_CLOSE);
	else
		send_reply(control_sock, FTP_CONN_DATA_ERR);
}

//
static void pipe_handler(int sig)
{
	psignal(sig, "ERROR");
}

static int handle_terminaison_signals(void)
{
	if (signal(SIGTERM, term_handler) == SIG_ERR)
		return (-1);
	if (signal(SIGINT, term_handler) == SIG_ERR)
		return (-1);
	if (signal(SIGQUIT, term_handler) == SIG_ERR)
		return (-1);
	if (signal(SIGUSR1, close_data_transfer) == SIG_ERR)
		return (-1);
	if (signal(SIGUSR2, close_data_transfer) == SIG_ERR)
		return (-1);
	//
	if (signal(SIGPIPE, pipe_handler) == SIG_ERR)
		return (-1);
	//
	return (0);
}

static pid_t create_data_transfer_process(int *child_io)
{
	int pipefd[4];
	pid_t dtp;

	if (pipe(pipefd) < 0 || pipe(pipefd + 2) < 0) {
		fprintf(stderr, "Error: pipe DTP\n");
		return (-1);
	}
	dtp = fork();
	if (dtp < 0) {
		fprintf(stderr, "Error: DTP\n");
		return (-1);
	} else if (dtp == 0) {
		close(pipefd[1]);
		close(pipefd[2]);
		dup2(pipefd[0], 0);
		dup2(pipefd[3], 1);
		data_transfer_process();
		exit(EXIT_SUCCESS);
	} else {
		close(pipefd[0]);
		close(pipefd[3]);
		child_io[0] = pipefd[2];
		child_io[1] = pipefd[1];
		printf("IO: %d, %d\n", child_io[0], child_io[1]);
		return (dtp);
	}
}

int dtp_io[2];
pid_t dtp;

void protocol_interpreter(int cs)
{
	char line[128];
	char *command;
	int ret;

	control_sock = cs; //
	if (handle_terminaison_signals() < 0)
		die(control_sock);
	dtp = create_data_transfer_process(dtp_io);
	if (dtp < 0) {
		send_reply(control_sock, FTP_CONN_CTRL_ERR);
		exit(EXIT_FAILURE);
	}
	printf("IO: %d, %d\n", dtp_io[0], dtp_io[1]);
	send_reply(control_sock, FTP_CONN_CTRL_READY);
	while ((ret = read_line(control_sock, line, sizeof(line))) > 0) {
		if (ret > 1) {
			send_reply(control_sock, FTP_SYNT_TOO_LONG);
			continue ;
		}
		printf("[%s]\n", line); //
		command = strtok(line, " ");
		if (ftp_exec(command, control_sock) < 0)
			die(control_sock);
	}
	kill(dtp, SIGTERM);
	wait4(dtp, NULL, 0, NULL);
	close(control_sock);
	exit(ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
