/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 07:40:07 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/10 17:14:59 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <sys/wait.h>
# include <arpa/inet.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h> // atoi
# include <stdio.h>
# include <string.h> // remove

# include "replies.h"

# define EOL "\r\n"

int server(const char *port);
void protocol_interpreter(int ctrl);
int reply(int ctrl, const char *str);

int read_line(int fd, char *buf, size_t bufsz);

#endif /* SERVER_H */
