/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:20:56 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/17 07:00:46 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

struct ftp_client client;

int print_working_directory(int control_sock)
{
	char reply[PATH_MAX + 7];

	if (!client.user) {
		send_reply(control_sock, FTP_AUTH_USER_ERR);
		return (1);
	}
	write(1, client.user->pw_name, strlen(client.user->pw_name));
	if (getcwd(reply + 5, PATH_MAX) == NULL) {
		send_reply(control_sock, FTP_FILE_PWD_ERR);
		return (2);
	}
	memcpy(reply, "257 \"", 5);
	strcat(reply, "\"");
	send_reply(control_sock, reply);
	return (0);
}
