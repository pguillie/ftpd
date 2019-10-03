/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 08:39:14 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/03 11:00:01 by pguillie         ###   ########.fr       */
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

struct connection {
	struct sockaddr_in addr;
	int sock;
};

struct ftp_session {
	/* system user */
	struct {
		/* logged user's password information */
		char *name;		/* username */
		uid_t uid;		/* user ID */
		gid_t gid;		/* group ID */
		char dir[PATH_MAX];	/* home directory */
		/* login in user */
		char *login;		/* login name */
	} user;
	/* connections */
	struct connection control;    /* control connection */
	struct connection data;	      /* data connection */
	enum ftp_data_type data_type; /* data representation type */
	/* FTP command */
	int (*command)(struct ftp_session *this); /* command to execute */
	char *args;		/* command's arguments */
	/* process information */
	long lnmax;	/* login name maximum length */
	int pipefd;	/* pipe's write end, used to log user */
};

#endif /* FTP_STRUCT_H */
