/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:20:56 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/12 15:40:08 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

int pwd(char **arg __attribute__((unused)), int control_sock)
{
	char path[PATH_MAX], *reply;

	if (getcwd(path, sizeof(path)) == NULL) {
		send_reply(control_sock, "550 Working directory unavailable.");
		return (2);
	}
	reply = (char *)malloc(strlen(path) + 7);
	if (reply == NULL)
		return (-1);
	strcpy(reply, "257 \"");
	strcat(reply, path);
	strcat(reply, "\"");
	send_reply(control_sock, reply);
	free(reply);
	return (0);
}
