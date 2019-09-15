/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 08:39:14 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/15 14:38:03 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_STRUCT_H
# define FTP_STRUCT_H

# include <arpa/inet.h>
# include <pwd.h>

enum ftp_data_type {
	TYPE_ASCII,
	TYPE_IMAGE
};

struct connection {
	struct sockaddr_in addr;
	int sock;
};

struct ftp_session {
	struct passwd user;
	char user_buf[1024];
	struct connection control;
	struct connection data;
	int (*command)(struct ftp_session *this);
	char *args;
	enum ftp_data_type data_type;
	int pipefd;
};

#endif /* FTP_STRUCT_H */
