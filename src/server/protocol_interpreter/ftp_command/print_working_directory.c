/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:20:56 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/04 11:06:57 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/protocol_interpreter.h"

int print_working_directory(char *arguments __attribute__((unused)))
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL) {
		send_reply(client.control.sock, FTP_FILE_PWD_ERR);
		return (2);
	}
	send_reply(client.control.sock, FTP_FILE_PWD_OK, cwd);
	return (0);
}
