/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/16 16:28:35 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

struct ftp_client client;

int user_name(int control_sock)
{
	char *name;
	struct passwd *pw;

	client.user = NULL;
	name = strtok(NULL, " ");
	if (name == NULL || strtok(NULL, " ") != NULL) {
		send_reply(control_sock, FTP_SYNT_USAGE_USER);
		return (1);
	}
	pw = getpwnam(name);
	if (pw == NULL || pw->pw_uid == 0) {
		send_reply(control_sock, FTP_AUTH_USER_ERR);
		return (1);
	}
	if (chdir(pw->pw_dir) < 0) {
		perror("chdir");
		die(control_sock);
	}
	if (setgid(pw->pw_gid) < 0) {
		perror("setgid");
		die(control_sock);
	}
	if (setuid(pw->pw_uid) < 0) {
		perror("setuid");
		die(control_sock);
	}
	client.user = pw;
	send_reply(control_sock, FTP_AUTH_USER_OK);
	system("id"); //process still belongs to group `0(root)'.
	return (0);
}
