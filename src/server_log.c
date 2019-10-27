/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 09:50:58 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/27 11:33:29 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

void server_log(const char *msg, struct sockaddr *addr, socklen_t addr_len)
{
	char host[128], port[8], date[32];
	int s;

	strftime(date, sizeof(date), "%a %b %d %T %Y",
		localtime(&(time_t){time(NULL)}));
	s = getnameinfo(addr, addr_len, host, sizeof(host),
		port, sizeof(port), NI_NUMERICSERV);
	if (s != 0) {
		ft_memcpy(host, "xxxx", 5);
		ft_memcpy(port, "xx", 3);
	}
	printf("[%s] %s:%s id:%d,%d\t%s\n", date, host, port,
		getuid(), getgid(), msg);
}
