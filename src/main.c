/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:33:19 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/27 10:11:45 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "server.h"

int main(int argc, char *argv[])
{
	char *port;

	if (getuid() == 0) {
		if (argc > 2) {
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			return 1;
		}
	} else {
		if (argc != 2) {
			fprintf(stderr, "Usage: %s <port>\n", argv[0]);
			return 1;
		}
		fprintf(stderr, "Warning: you are running this service as a "
			"regular user. Anyone will be able to connect to your "
			"account without providing any password.\n"
			"To allow this service to manage passwords, "
			"please run it as root: stop this process and type "
			"``sudo !!''\n");
	}
	port = argv[1];
	return server(port);
}
