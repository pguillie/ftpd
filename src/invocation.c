/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:42:52 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/23 12:07:45 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

static int root_usage(const char *bin)
{
	fprintf(stderr, "Usage: %s [port]\n", bin);
	return 1;
}

static int user_usage(const char *bin)
{
	fprintf(stderr, "Usage: %s <port>\n", bin);
	return 1;
}

int invocation(int argc, char *argv[], char **port)
{
	if (getuid() == 0) {
		if (argc > 2)
			return root_usage(argv[0]);
	} else {
		if (argc != 2)
			return user_usage(argv[0]);
	}
	*port = argv[1];
	return 0;
}
