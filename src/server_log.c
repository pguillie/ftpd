/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 09:50:58 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/26 12:36:14 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netdb.h>
#include <stdio.h>
#include <time.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

void server_log(const char *msg, struct sockaddr *addr, socklen_t addr_len)
{
	char host[128], port[8], buf[32];
	int s;

	strftime(buf, sizeof(buf), "[%a %b %d %T %Y] ",
		localtime(&(time_t){time(NULL)}));
	s = getnameinfo(addr, addr_len, host, sizeof(host),
		port, sizeof(port), NI_NUMERICSERV);
	printf(buf);
	if (s != 0)
		printf("(unknown address) ");
	else
		printf(ft_strchr(host, ':') ? "[%s]:%s " : "%s:%s ",
			host, port);
	printf("%s\n", msg);
}
