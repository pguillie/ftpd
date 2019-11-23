/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_service.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:14:02 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/23 12:20:24 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "../libft/include/libft.h"

#define LISTEN_BACKLOG (8)

static int use_addr(struct addrinfo addr)
{
	int s;

	do {
		s = socket(addr.ai_family, addr.ai_socktype, addr.ai_protocol);
		if (s == -1)
			break;
		setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
		if (bind(s, addr.ai_addr, addr.ai_addrlen))
			break;
		if (listen(s, LISTEN_BACKLOG) < 0)
			break;
		return s;
	} while (0);
	close(s);
	return -1;
}

static int find_interface(struct addrinfo *rp)
{
	int sfd = -1;

	if (rp == NULL)
		return -1;
	if (rp->ai_family == AF_INET6) {
		sfd = use_addr(*rp);
		if (sfd == -1)
			return find_interface(rp->ai_next);
	} else {
		sfd = find_interface(rp->ai_next);
		if (sfd == -1)
			return use_addr(*rp);
	}
	return sfd;
}

int run_service(const char *service)
{
	struct addrinfo hints, *result;
	int sfd;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_PASSIVE;
	if (!service)
		service = "ftp";
	if (getaddrinfo(NULL, service, &hints, &result) != 0)
		return -1;
	sfd = find_interface(result);
	freeaddrinfo(result);
	return sfd;
}
