/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 07:40:07 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/27 11:54:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOCOL_INTERPRETER_H
# define PROTOCOL_INTERPRETER_H

# include "ftp_reply.h"
# include "ftp_struct.h"

int session_manager(int sock, struct sockaddr_in connected_socket);

int protocol_interpreter(struct ftp_session *session);

int set_command(struct ftp_session *session, char *cmd_line);
int recv_command(int sock, char *command, size_t commandsz);
int send_reply(int sock, enum ftp_reply_code rep_idx, ...);
void send_dtp_reply(int sock, enum ftp_reply_code rep_idx);

void close_session(struct ftp_session *session);
void die(struct ftp_session *session);

#endif /* PROTOCOL_INTERPRETER_H */
