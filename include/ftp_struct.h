/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 08:39:14 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/28 12:38:22 by pguillie         ###   ########.fr       */
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
	struct passwd user;	/* user logged in */
	char login[128];	/* user login in */
	char user_buf[1024];	/* logged user information */
	struct connection control; /* control connection */
	struct connection data;	/* data connection */
	int (*command)(struct ftp_session *this); /* command to execute */
	char *args;		/* command's arguments */
	enum ftp_data_type data_type; /* data representation type */
	int pipefd;		/* pipe's write end, send session to log user */
};

#endif /* FTP_STRUCT_H */
