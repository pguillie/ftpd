/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_command.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:28:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/23 08:09:11 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_COMMAND_H
# define FTP_COMMAND_H

# include "ftp_struct.h"

/* ACCESS CONTROL COMMANDS */

int ftp_user(struct ftp_session *session);
int ftp_pass(struct ftp_session *session);
int ftp_cwd(struct ftp_session *session);
int ftp_quit(struct ftp_session *session);

/* TRANSFER PARAMETER COMMANDS */

int ftp_port(struct ftp_session *session);
int ftp_type(struct ftp_session *session);
int ftp_eprt(struct ftp_session *session);

/* FTP SERVICE COMMANDS */

int ftp_retr(struct ftp_session *session);
int ftp_stor(struct ftp_session *session);
int ftp_abor(struct ftp_session *session);
int ftp_pwd(struct ftp_session *session);
int ftp_list(struct ftp_session *session);
int ftp_syst(struct ftp_session *session);
int ftp_noop(struct ftp_session *session);

#endif /* FTP_COMMAND_H */
