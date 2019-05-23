/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 07:40:07 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/23 17:07:21 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOCOL_INTERPRETER_H
# define PROTOCOL_INTERPRETER_H

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

# include "../libft/include/libft.h"
# include "replies.h"
# include "ftp_command.h"

# define EOL "\r\n"
# define EOL_LENGTH (2)

struct connected_socket {
	struct sockaddr_in addr;
	int sock;
};

struct ftp_client {
	struct passwd *user;
	struct connected_socket control;
	struct connected_socket data;
};

enum e_dtp_type {
	DTP_LIST,
	DTP_RETRIEVE,
	DTP_STORE,
	DTP_TYPE_NUMBER
};

int server(const char *port);
int protocol_interpreter(struct connected_socket control);
/* void data_transfer_process(void); */
int send_reply(const char *reply);
int ftp_exec(const char *command, char *arguments);
void die(void);

int data_transfer_process(enum e_dtp_type id, const char *file);
int dtp_list(int data_sock, const char *file);

extern struct ftp_client client;

#endif /* PROTOCOL_INTERPRETER_H */
