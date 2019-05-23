/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:20:56 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/23 16:56:47 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

int print_working_directory(char *arguments __attribute__((unused)))
{
	char reply[PATH_MAX + 7];

	if (getcwd(reply + 5, PATH_MAX) == NULL) {
		send_reply(FTP_FILE_PWD_ERR);
		return (2);
	}
	memcpy(reply, "257 \"", 5);
	strcat(reply, "\"");
	send_reply(reply);
	return (0);
}
