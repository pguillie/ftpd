/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 07:40:07 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/16 16:19:39 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <sys/wait.h>
# include <arpa/inet.h>
# include <signal.h>
# include <pwd.h>
# include <unistd.h>
# include <stdlib.h> // atoi
# include <stdio.h>
# include <fcntl.h>
# include <string.h> // remove
# include <limits.h>
# include <ctype.h>

# include "replies.h"
# include "ftp_command.h"

# define EOL "\r\n"
# define EOL_LENGTH (2)

int server(const char *port);
void protocol_interpreter(int control_sock);
int send_reply(int control_sock, const char *reply);
int ftp_exec(const char *command, int control_sock);
void die(int control_sock);

int read_line(int fd, char *buf, size_t bufsz);
int get_next_line(int fd, char **line);

struct ftp_client {
	struct passwd *user;
	struct sockaddr_in ctrl;
	struct sockaddr_in data;
};

extern struct ftp_client client;

#endif /* SERVER_H */
