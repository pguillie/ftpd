/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/03 19:31:49 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "protocol_interpreter.h"

struct ftp_client client;

int user_name(char *arguments)
{
	char *name;
	struct passwd *pw;

	client.user = NULL;
	name = strtok(arguments, " ");
	if (name == NULL || strtok(NULL, " ") != NULL) {
		send_reply(client.control.sock, FTP_SYNT_ERR);
		return (1);
	}
	pw = getpwnam(name);
	if (pw == NULL || pw->pw_uid == 0) {
		send_reply(client.control.sock, FTP_AUTH_ERR);
		return (1);
	}
	if (chdir(pw->pw_dir) < 0) {
		perror("chdir");
		die();
	}
	if (setgid(pw->pw_gid) < 0) {
		perror("setgid");
		die();
	}
	if (setuid(pw->pw_uid) < 0) {
		perror("setuid");
		die();
	}
	client.user = pw;
	send_reply(client.control.sock, FTP_AUTH_OK);
	return (0);
}
