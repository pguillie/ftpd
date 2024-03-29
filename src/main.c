/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 12:33:19 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/23 12:02:45 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int main(int argc, char *argv[])
{
	char *port;

	if (invocation(argc, argv, &port) != 0)
		return 1;
	return server(port);
}
