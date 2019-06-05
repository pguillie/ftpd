/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_reply.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:58:46 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/05 19:04:15 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_REPLY_H
# define FTP_REPLY_H

# define REPLY_BUFFER_SIZE 128

struct reply_buffer {
	char buf[REPLY_BUFFER_SIZE];
	size_t i;
	int hyphen;
};

enum ftp_reply_code {
	FTP_SYNT_CMD_OK,
	FTP_SYNT_ERR,
	FTP_SYNT_OK,
	FTP_SYNT_TOO_LONG,
	FTP_INFO_SYS_TYPE,
	FTP_CONN_ABORT_OK,
	FTP_CONN_ABORT_ERR,
	FTP_CONN_CTRL_CLOSE,
	FTP_CONN_CTRL_ERR,
	FTP_CONN_CTRL_READY,
	FTP_CONN_DATA_CLOSE,
	FTP_CONN_DATA_ERR,
	FTP_AUTH_ERR,
	FTP_AUTH_OK,
	FTP_FILE_CWD_ERR,
	FTP_FILE_CWD_OK,
	FTP_FILE_LOCAL_ERR,
	FTP_FILE_ERR,
	FTP_FILE_LIST_ERR,
	FTP_FILE_LIST_OPEN,
	FTP_FILE_PWD_ERR,
	FTP_FILE_PWD_OK,
	FTP_FILE_RETR_OPEN,
	FTP_FILE_STOR_OPEN,
	FTP_FILE_TRANSFR_ERR,
};

/* # define FTP_SYNT_OK		"200 Command okay." */
/* # define FTP_SYNT_PORT		"200 PORT successfully interpreter." */
/* # define FTP_SYNT_ERR		"500 Syntax error, command unrecognized." */
/* # define FTP_SYNT_TOO_LONG	"500 Command line too long." */
/* # define FTP_SYNT_ARG_ERR	"501 Syntax error in parameters or arguments." */
/* # define FTP_SYNT_NOT_IMPL	"502 Command not implemented." */

/* # define FTP_INFO_SYS_TYPE	"215 UNIX system type." */

/* # define FTP_CONN_CTRL_READY	"220 Service ready for new user." */
/* # define FTP_CONN_CTRL_CLOSE	"221 Service closing control connection. Goodbye." */
/* # define FTP_CONN_DATA_CLOSE	"226 Closing data connection." */
/* # define FTP_CONN_RETR_SUCCS	"226 RETR successfull, closing data connection." */
/* # define FTP_CONN_STOR_SUCCS	"226 STOR successfull, closing data connection." */
/* # define FTP_CONN_LIST_SUCCS	"226 LIST successfull, closing data connection." */
/* # define FTP_CONN_CTRL_ERR	"421 Service not available, closing control connection." */
/* # define FTP_CONN_DATA_OPEN_ERR	"425 Can't open data connection." */
/* # define FTP_CONN_DATA_ERR	"426 Connection closed; transfer aborted." */
/* # define FTP_AUTH_USER_OK	"230 User logged in, proceed." */
/* # define FTP_AUTH_USER_ERR	"530 Not logged in." */

/* # define FTP_FILE_DATA_OK	"150 File status okay; about to open data connection." */
/* # define FTP_FILE_LIST_START	"150 Listing directory..." */
/* # define FTP_FILE_RETR_START	"150 Sending file..." */
/* # define FTP_FILE_STOR_START	"150 Receving file..." */
/* # define FTP_FILE_CWD_OK	"250 Working directory changed." */
/* # define FTP_FILE_LIST_ERR	"450 File unavailable." */
/* # define FTP_FILE_ERR		"550 File unavailable." */
/* # define FTP_FILE_CWD_ERR	"550 Unable to change working directory." */
/* # define FTP_FILE_PWD_ERR	"550 Working directory unavailable." */

#endif /* FTP_REPLY_H */
