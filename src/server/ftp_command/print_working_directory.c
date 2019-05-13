/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:20:56 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/13 07:57:53 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

int print_working_directory(int control_sock)
{
	char reply[PATH_MAX + 7];

	if (getcwd(reply + 5, PATH_MAX) == NULL) {
		send_reply(control_sock, FTP_FILE_PWD_ERR);
		return (2);
	}
	memcpy(reply, "257 \"", 5);
	strcat(reply, "\"");
	send_reply(control_sock, reply);
	return (0);
}
