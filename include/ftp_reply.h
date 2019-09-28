/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_reply.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:58:46 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/28 12:34:03 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_REPLY_H
# define FTP_REPLY_H

#include <stddef.h>

# define REPLY_BUFFER_SIZE 128

struct reply_buffer {
	char buf[REPLY_BUFFER_SIZE];
	size_t i;
	int hyphen;
};

enum ftp_reply_code {
	FTP_SYNT_BAD_SEQ,
	FTP_SYNT_CMD_OK,
	FTP_SYNT_ERR,
	FTP_SYNT_OK,
	FTP_SYNT_TOO_LONG,
	FTP_SYNT_NOT_IMPL,
	FTP_SYNT_NOT_IMPL_PARA,
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
	FTP_AUTH_PASS,
	FTP_AUTH_USAGE,
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

#endif /* FTP_REPLY_H */
