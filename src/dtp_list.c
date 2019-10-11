/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:30:37 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/26 09:49:59 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include "data_transfer_process.h"
#include "ftp_reply.h"

#define LS	"/bin/ls"
#define LS_OPT	"-l"

int dtp_list(struct ftp_session *session)
{
	int pipefd[2], ret, success;
	pid_t ls;

	if (pipe(pipefd) < 0)
		return FTP_FILE_LOCAL_ERR;
	ls = fork();
	if (ls < 0) {
		return 1;
	} else if (ls == 0) {
		close(pipefd[0]);
		close(session->data.sock);
		dup2(pipefd[1], 1);
		dup2(pipefd[1], 2);
		if (execl(LS, LS, LS_OPT, session->args, NULL))
			exit(FTP_FILE_LOCAL_ERR);
	}
	close(pipefd[1]);
	success = send_data(session->data.sock, pipefd[0], session->data_type);
	wait4(ls, &ret, 0, NULL);
	if (success < 0)
		return FTP_CONN_ABORT_ERR;
	if (!WIFEXITED(ret))
		return FTP_FILE_LOCAL_ERR;
	return FTP_CONN_DATA_CLOSE;
}
