/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 10:54:58 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/12 06:15:15 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ftp_struct.h"

void close_session(struct ftp_session *session)
{
	close(session->control.sock);
	/* ... */
}
