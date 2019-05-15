/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:40:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/15 17:33:43 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

/* global:
 *
 * user
 * account
 */

static char *get_user_info(const char *user, int control_sock)
{
	int fd, ret;
	char *line;
	size_t len;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd < 0)
		die(control_sock);
	len = strlen(user);
	while ((ret = get_next_line(fd, &line)) > 0) {
		if (strncmp(line, user, len) == 0 && line[len] == ':')
			return (line);
		free(line);
	}
	if (ret < 0)
		die(control_sock);
	return (NULL);
}

static int set_user_id(char *info)
{
	int id[2];
	size_t i, n = 4;

	i = 0;
	while (n--) {
		while (info[i] && info[i] != ':')
			i++;
		if (n < sizeof(id) / sizeof(id[0]))
			id[sizeof(id) / sizeof(id[0]) - n - 1] = atoi(info);
		info += i + (info[i] ? 1 : 0);
		i = 0;
	}
//	setgid(0);
	seteuid(0);
	if (setgid(id[1]) < 0 || seteuid(id[0]) < 0)
		return (-1);
	return (0);
}

static int set_user_home(char *info)
{
	size_t i, n = 6;

	i = 0;
	while (n--) {
		info += i + (info[i] ? 1 : 0);
		i = 0;
		while (info[i] && info[i] != ':')
			i++;
	}
	info[i] = '\0';
	if (chdir(info) < 0)
		return (-1);
	return (0);
}

int user_name(int control_sock)
{
	char *user, *user_info;

	printf("current id : %d\n", getuid());
	user = strtok(NULL, " ");
	if (user == NULL || strtok(NULL, " ")) {
		send_reply(control_sock, FTP_SYNT_ARG_ERR);
		return (1);
	}
	user_info = get_user_info(user, control_sock);
	if (user_info == NULL) {
		send_reply(control_sock, FTP_AUTH_USER_ERR);
		return (1);
	}
	if (set_user_id(user_info) < 0 || set_user_home(user_info) < 0) {
		free(user_info);
		die(control_sock);
	}
	free(user_info);
	if (geteuid() == 0) {
		send_reply(control_sock, FTP_AUTH_USER_ERR);
		return (1);
	}
	send_reply(control_sock, FTP_AUTH_USER_OK);
	return (0);
}
