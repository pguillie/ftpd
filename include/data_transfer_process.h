/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_transfer_process.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 12:53:25 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:30:28 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_TRANSFER_PROCESS_H
# define DATA_TRANSFER_PROCESS_H

# include "ftp_struct.h"

int data_transfer_process(struct ftp_session *session);
int dtp_retr(struct ftp_session *session);
int dtp_stor(struct ftp_session *session);
int dtp_list(struct ftp_session *session);

int recv_data(int sock, int fd, enum ftp_data_type type);
int send_data(int sock, int fd, enum ftp_data_type type);

#endif /* DATA_TRANSFER_PROCESS_H */
