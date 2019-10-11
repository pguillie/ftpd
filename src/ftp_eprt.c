/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_eprt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:55:26 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/26 12:45:26 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "protocol_interpreter.h"
#include "../libft/include/libft.h"

static int is_valid_syntax(const char *eaddr)
{
	size_t i;
	char delim;

	delim = *eaddr++;
	if (delim < 33 || delim > 126)
		return 0;
	while (*eaddr != delim)
		if (!ft_isdigit(*eaddr++))
			return 0;
	eaddr++;
	i = 0;
	while (eaddr[i] && eaddr[i] != delim)
		i++;
	if (eaddr[i] != delim || !i || i > 128)
		return 0;
	eaddr += i + 1;
	i = 0;
	while (eaddr[i] != delim)
		if (!ft_isdigit(eaddr[i++]))
			return 0;
	if (!i || i > 8)
		return 0;
	eaddr += i + 1;
	return (*eaddr == '\0' ? 1 : 0);
}

int ftp_eprt(struct ftp_session *session)
{
	char *eaddr, delim;
	size_t i;

	if (!session->user.pw_uid) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	}
	eaddr = session->args;
	if (eaddr == NULL || !is_valid_syntax(eaddr)) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	delim = *eaddr++;
	while (*eaddr++ != delim) ;
	i = 0;
	while (*eaddr != delim)
		session->data.host[i++] = *eaddr++;
	session->data.host[i] = '\0';
	eaddr++;
	i = 0;
	while (*eaddr != delim)
		session->data.port[i++] = *eaddr++;
	session->data.port[i] = '\0';
	send_reply(session->control.sock, FTP_SYNT_CMD_OK, "EPRT");
	return 0;
}
