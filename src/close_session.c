/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_session.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 10:54:58 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/04 14:10:49 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ftp_struct.h"

void close_session(struct ftp_session *session)
{
	close(session->control.sock);
	close(session->pipefd);
}
