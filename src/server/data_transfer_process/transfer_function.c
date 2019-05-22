/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 12:57:14 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/21 13:26:37 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/data_transfer_process.h"

struct sockaddr_in client_dtp;

static struct {
	char c;
	int (*f)(const char *file);
} dtp_command[] = {
	{'l', dtp_list},
	{'p', dtp_port},
	/* {'r', dtp_retrieve}, */
	/* {'s', dtp_store}, */
};

void transfer_function(const char *transfer)
{
	size_t i;

	i = 0;
	while (i < sizeof(dtp_command) / sizeof(dtp_command[0])) {
		if (transfer[0] == dtp_command[i].c)
			dtp_command[i].f(transfer + 1);
		i++;
	}
}
