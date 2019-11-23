/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   login.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 10:43:05 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/24 12:36:17 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int login(struct passwd *pwd)
{
	if (!pwd || pwd->pw_uid == 0)
		return 0;
	if (setgid(pwd->pw_gid) < 0
		|| initgroups(pwd->pw_name, pwd->pw_gid) < 0
		|| setuid(pwd->pw_uid) < 0
		||chdir(pwd->pw_dir) < 0)
		return -1;
	return 1;
}
