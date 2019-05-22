/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:14:14 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/20 16:34:11 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <sys/wait.h>
# include <arpa/inet.h>
# include <stdio.h>

#include <stdlib.h>

struct socket_info {
	struct sockaddr_in addr;
	int sock;
};

int server(const char *port);
//int protocol_interpreter(struct socket_info control);

#endif /* SERVER_H */
