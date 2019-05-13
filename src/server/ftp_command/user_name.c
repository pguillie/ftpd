/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/13 14:39:20 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

/* global:
 *
 * user
 * account
 */

static char *user_home(char *line)
{
	int i = 5;
	char *field;

	while (i--) {
		field = strsep(&line, ":");
		if (field == NULL)
			return (NULL);
	}
	return (strdup(field));
}

static char *get_user_home(const char *user, int control_sock)
{
	int fd = open("/etc/passwd", O_RDONLY);
	char *line, *name, *home;
	int ret;

	if (fd < 0)
		die(control_sock);
	while ((ret = get_next_line(fd, &line)) > 0) {
		name = strsep(&line, ":");
		if (name && strcmp(name, user) == 0) {
			home = user_home(line);
			free(name);
			return (home);
		}
		free(name);
	}
	if (ret < 0)
		die(control_sock);
	return (NULL);
}

int user_name(int control_sock)
{
	char *user, *home;
	int failure;

	user = strtok(NULL, " ");
	if (user == NULL || strtok(NULL, " ")) {
		send_reply(control_sock, FTP_SYNT_ARG_ERR);
		return (1);
	}
	home = get_user_home(user, control_sock);
	if (!home) {
		send_reply(control_sock, FTP_AUTH_USER_ERR);
		return (1);
	}
	failure = chdir(home);
	free(home);
	if (failure)
		die(control_sock);
	send_reply(control_sock, FTP_AUTH_USER_OK);
	return (0);
}
