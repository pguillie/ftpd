/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 09:09:49 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/23 12:49:42 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#include "server.h"

static void child_handler(int sig __attribute__((unused)))
{
	wait4(-1, NULL, 0, NULL);
}

int server(const char *service)
{
	int lsoc;
	int ret;

	lsoc = run_service(service);
	if (lsoc < 0) {
		fprintf(stderr, "Error: unable to create server\n");
		return 1;
	}
	if (signal(SIGCHLD, child_handler) == SIG_ERR)
		return 2;
	//log server addr + warning if reg. user
	ret = connection_manager(lsoc);
	close(lsoc);
	return (ret == 0) ? 0 : 1;
}
