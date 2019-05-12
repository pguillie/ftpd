/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:58:46 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/11 10:28:38 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_H
# define REPLIES_H

# define FTP_SYNT_OK		"200 Command okay."
# define FTP_SYNT_ERR		"500 Syntax error, command unrecognized."
# define FTP_SYNT_TOO_LONG	"500 Command line too long."
# define FTP_SYNT_ARG_ERR	"501 Syntax error in parameters or arguments."
# define FTP_SYNT_NOT_IMPL	"502 Command not implemented."

# define FTP_INFO_SYS_TYPE	"215 UNIX system type."

# define FTP_CONN_CTRL_READY	"220 Service ready for new user."
# define FTP_CONN_CTRL_CLOSE	"221 Service closing control connection."
# define FTP_CONN_CTRL_ERR	"421 Service not available, closing control connection."

# define FTP_AUTH_USER_OK	"230 User logged in, proceed."
# define FTP_AUTH_USER_ERR	"530 Not logged in."

#endif /* REPLIES_H */
