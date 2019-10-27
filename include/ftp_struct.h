/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 08:39:14 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/27 14:33:28 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_STRUCT_H
# define FTP_STRUCT_H

# include <arpa/inet.h>
# include <limits.h>

enum ftp_data_type {
	TYPE_ASCII,
	TYPE_IMAGE
};

struct ftp_session {
	int auth;
	char home[PATH_MAX];
	struct {
		struct sockaddr_storage addr;
		socklen_t addr_len;
		int sock;
	} control;
	struct {
		char host[128];
		char port[8];
		int sock;
	} data;
	int (*command)(struct ftp_session *this);
	char *args;
	enum ftp_data_type data_type;
	int pipefd;
};

#endif /* FTP_STRUCT_H */
