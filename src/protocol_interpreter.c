/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:51:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/15 15:03:48 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

#include <stdio.h> //fprintf

#include "protocol_interpreter.h"
#include "ftp_struct.h"
#include "dtp.h"
#include "../libft/include/libft.h"

pid_t dtp = -1;

static void dtp_reply(int sock, enum ftp_reply_code rep_idx)
{
	static int _sock;

	if (sock >= 0)
		_sock = sock;
	send_reply(_sock, rep_idx);
}

static void dtp_exit_status(int sig __attribute__((unused)))
{
	int ftp_reply_code;

	wait4(dtp, &ftp_reply_code, 0, NULL);
	dtp = -1;
	if (WIFEXITED(ftp_reply_code))
		dtp_reply(-1, WEXITSTATUS(ftp_reply_code));
	else
		dtp_reply(-1, FTP_FILE_LOCAL_ERR);
}

static int init_session(struct ftp_session *session, int sock,
	struct sockaddr_in addr)
{
	int pipefd[2];

	if (pipe(pipefd) < 0) {
		dtp_reply(sock, FTP_CONN_CTRL_ERR);
		return -1;
	}
	session->control = (struct connection){addr, sock};
	ft_memset(&(session->user), 0, sizeof(session->user));
	ft_memset(&(session->data), 0, sizeof(session->data));
	session->command = NULL;
	session->args = NULL;
	session->data_type = TYPE_ASCII;
	session->pipefd = pipefd[1];
	dtp_reply(session->control.sock, FTP_CONN_CTRL_READY);
	return pipefd[0];
}

static int log_user(struct ftp_session *session)
{
	printf("log user %s\n", session->user.pw_name);
////////
	if (setgid(session->user.pw_gid) < 0)
		perror("setgid");
	if (initgroups(session->user.pw_name, session->user.pw_gid) < 0){
		perror("initgroups");
		printf("%s, %d\n", session->user.pw_name, session->user.pw_gid);
	}
	if (setuid(session->user.pw_uid) < 0)
		perror("setuid");
////////
// GET DTP ERROR REPLY WHEN LOGING
	if (session->user.pw_uid == 0 || session->user.pw_gid == 0
		|| setgid(session->user.pw_gid) < 0
//		|| initgroups(session->user.pw_name, session->user.pw_gid) < 0
		|| setuid(session->user.pw_uid) < 0) {
		ft_memset(&(session->user), 0, sizeof(session->user));
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	if (chdir(session->user.pw_dir) < 0)
		die(session);
	send_reply(session->control.sock, FTP_AUTH_OK);
	return 0;
}

int protocol_interpreter(int sock, struct sockaddr_in addr)
{
	struct ftp_session session;
	char line[128];
	int ret, status, pipefd;
	pid_t user;

	pipefd = init_session(&session, sock, addr);
	if (pipefd < 0) {
		fprintf(stderr, "Error: pipe");
		return -1;
	}
	while (1) {
		printf("fork!\n");
		user = fork();
		if (user < 0) {
			die(&session);
		} else if (user == 0) {
			close(pipefd);
			if (signal(SIGCHLD, dtp_exit_status) == SIG_ERR)
				die(&session);
			if (session.user.pw_uid != 0)
				log_user(&session);
			else
				printf("USER NULL\n");
			while ((ret = recv_command(session.control.sock, line,
						sizeof(line))) > 0) {
				if (ret > 1) {
					send_reply(session.control.sock, FTP_SYNT_TOO_LONG);
					continue ;
				}
				system("id");
				printf("TYPE = %d\n", session.data_type);
				if (set_command(&session, line) != 0)
					send_reply(session.control.sock, FTP_SYNT_ERR);
				else if (session.command(&session) < 0)
					die(&session);
			}
			close_session(&session);
			exit(ret == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
		} else {
			wait4(user, &status, 0, NULL);
			if (read(pipefd, &session, sizeof(session) + 1)
				!= sizeof(session)) {
				printf("Read more or less bytes than session's size!\n");
				break ;
			}
			printf("received struct !\nUSER = %s\n", session.user.pw_name);
		}
	}
	close(pipefd);
	return (status == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}
