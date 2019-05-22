/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_dtp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 12:53:25 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 13:26:21 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_DTP_H
# define SERVER_DTP_H

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

void transfer_function(const char *transfer);

int dtp_port(const char *sockaddr);
int dtp_list(const char *path);

int connect_dtp(void);
void close_dtp(int data_sock);

extern struct sockaddr_in client_dtp;

#endif /* SERVER_DTP_H */
