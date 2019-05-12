/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 11:38:21 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/12 15:52:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

static struct {
	const char *name;
	int (*f)(char **arg, int control_soc);
} ftp_command[] = {
	/* {"list", list}, */
	/* {"cwd", change_wdir}, */
	/* {"retr", retrieve}, */
	/* {"stor", store}, */
	{"pwd", pwd},
	/* {"quit", logout} */
};

static void free_str_array(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char **create_arg(void)
{
	char **arg, **array, *token;
	size_t n, i;

	arg = NULL;
	n = 1;
	while ((token = strtok(NULL, " "))) {
		n += 1;
		array = malloc(n);
		i = n - 1;
		array[i + 1] = NULL;
		array[i] = strdup(token);
		if (array[i] == NULL) {
			while (n--)
				free(arg[n]);
			free(arg);
			return (NULL);
		}
		while (i--)
			array[i] = arg[i];
		free(arg);
		arg = array;
	}
	return (arg);
}

int ftp_exec(const char *command, int control_sock)
{
	char code[5];
	char **arg;
	size_t i;
	int ret;

	if (command == NULL) {
		send_reply(control_sock, FTP_SYNT_ERR);
		return (1);
	}
	i = 0;
	while (*command && i < 5)
		code[i++] = tolower(*command++);
	if (*command != '\0') {
		send_reply(control_sock, FTP_SYNT_ERR);
		return (1);
	}
	code[i] = '\0';
	i = sizeof(ftp_command) / sizeof(ftp_command[0]);
	while (i--) {
		if (strcmp(ftp_command[i].name, code) == 0) {
			arg = create_arg();
			ret = ftp_command[i].f(arg, control_sock);
			if (arg)
				free_str_array(arg);
			return (ret);
		}
	}
	send_reply(control_sock, FTP_SYNT_ERR);
	return (1);
}
