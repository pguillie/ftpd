/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_interpreter.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 07:40:07 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/27 14:15:49 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOCOL_INTERPRETER_H
# define PROTOCOL_INTERPRETER_H

# include <pwd.h>

# include "ftp_reply.h"
# include "ftp_struct.h"

int session_manager(int sock, struct sockaddr_storage addr, socklen_t addr_len);
int auth(int pipefd, struct ftp_session *session, struct passwd **pwd);

int protocol_interpreter(struct ftp_session *session);
void server_log(const char *msg, struct sockaddr *addr, socklen_t addr_len);

int set_command(struct ftp_session *session, char *cmd_line);
int recv_command(int sock, char *command, size_t cmd_size);
int send_reply(int sock, enum ftp_reply_code rep_idx, ...);

void close_session(struct ftp_session *session);
void die(struct ftp_session *session);

char *chroot_home(const char *home, const char *path, char *chrooted);

#endif /* PROTOCOL_INTERPRETER_H */
