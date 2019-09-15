/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 10:54:58 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/15 11:43:25 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ftp_struct.h"

void close_session(struct ftp_session *session)
{
	close(session->control.sock);
	close(session->pipefd);
	/* ... */
}
