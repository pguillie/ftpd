/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:33:19 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/11 06:25:58 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "server.h"

int main(int argc, char *argv[])
{
	char *port;

	if (argc > 2) {
		fprintf(stderr, "Usage: %s [port]\n", argv[0]);
		return 1;
	}
	port = (argc == 2 ? argv[1] : "21");
	return server(port);
}
