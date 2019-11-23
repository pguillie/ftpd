/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 09:50:58 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/24 13:11:28 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static int is_password(const char *log)
{
	const char *pass = "PASS";
	size_t i;

	i = 0;
	while (*pass && (log[i++] | 32) == (*pass | 32))
		pass++;
	if (*pass != '\0' || log[i] != ' ')
		return 0;
	return 1;
}

void ftp_log(const char *msg, struct sockaddr_storage *addr, socklen_t addr_len)
{
	char host[128], port[8], date[32];
	int s;

	strftime(date, sizeof(date), "%a %b %d %T %Y",
		localtime(&(time_t){time(NULL)}));
	s = getnameinfo((struct sockaddr *)addr, addr_len, host, sizeof(host),
		port, sizeof(port), NI_NUMERICSERV);
	if (s != 0) {
		ft_memcpy(host, "xxxx", 5);
		ft_memcpy(port, "xx", 3);
	}
	if (is_password(msg))
		msg = "PASS *";
	printf("[%s] %s:%s id:%d,%d\t%s\n", date, host, port,
		getuid(), getgid(), msg);
}
