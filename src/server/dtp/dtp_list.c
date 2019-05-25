/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:30:37 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/25 11:23:50 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

struct ftp_client client;

int dtp_list(const char *file)
{
	int pipefd[2], ret;
	pid_t ls;

	if (pipe(pipefd) < 0)
		return (2);
	ls = fork();
	if (ls < 0) {
		return (1);
	} else if (ls == 0) {
		close(pipefd[0]);
		close(client.data.sock);
		dup2(pipefd[1], 1);
		dup2(pipefd[1], 2);
		if (execl("/bin/ls", "/bin/ls", "-l", file, NULL))
			return (2);
	}
	close(pipefd[1]);
	send_data(pipefd[0]);
	wait4(ls, &ret, 0, NULL);
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (2);
}
