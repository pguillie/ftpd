/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:51:01 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/10 17:12:30 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

void protocol_interpreter(int ctrl)
{
	char cmd[128];
	int ret;

	reply(ctrl, REP_READY);
	while ((ret = read_line(ctrl, cmd, sizeof(cmd))) > 0) {
		if (ret > 1) {
			reply(ctrl, REP_CMD_TOO_LONG);
			continue ;
		}
		printf("%s\n", cmd);
		reply(ctrl, REP_CMD_OK);
	}
	exit(EXIT_SUCCESS); // successo?
}
