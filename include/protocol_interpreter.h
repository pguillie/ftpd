/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 07:40:07 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/23 14:52:24 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOCOL_INTERPRETER_H
# define PROTOCOL_INTERPRETER_H

# include <sys/socket.h>
# include <sys/wait.h>
# include <arpa/inet.h>
# include <signal.h>
# include <stdarg.h>
# include <pwd.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <ctype.h>

# include "../libft/include/libft.h"
# include "ftp_command.h"
# include "ftp_reply.h"

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
	int binary;
};

enum e_dtp_type {
	DTP_RETR,
	DTP_STOR,
	DTP_LIST
};

int server(const char *port);
int protocol_interpreter(struct connected_socket control);
int recv_command(int control_sock, char *command, size_t commandsz);
int send_reply(int control_sock, enum ftp_reply_code rep_idx, ...);
int execute(const char *command, char *arguments);
void die(void);

int data_transfer_process(enum e_dtp_type id, const char *file);
int dtp_retr(const char *file);
int dtp_stor(const char *file);
int dtp_list(const char *file);

int recv_data(int data_sock, int fd);
int send_data(int data_sock, int fd);

extern struct ftp_client client;

#endif /* PROTOCOL_INTERPRETER_H */
