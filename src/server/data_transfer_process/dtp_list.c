/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:27:23 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 13:26:18 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/data_transfer_process.h"
#include "server/protocol_interpreter.h"

int dtp_list(const char *path)
{
	int data_sock;
	pid_t ls_pid;
	int wstatus;

	if (access(path, F_OK) != 0) {
		write(1, "450", 3);
		return (1);
	}
	data_sock = connect_dtp();
	if (data_sock < 0) {
		write(1, "425", 3);
		return (1);
	}
	ls_pid = fork();
	if (ls_pid < 0) {
		write(1, "421", 3);
		return (2);
	} else if (ls_pid == 0) {
		dup2(data_sock, 1);
		dup2(data_sock, 2);
		execl("/bin/ls", "/bin/ls", "-l", path, NULL);
		exit(EXIT_FAILURE);
	} else {
		wait4(ls_pid, &wstatus, 0, NULL);
	}
	close_dtp(data_sock);
	return (0);
}
