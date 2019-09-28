/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_pass.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 08:38:36 by pguillie          #+#    #+#             */
/*   Updated: 2019/09/28 12:39:41 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ftp_pass(struct ftp_session *session)
{
	char *pass;
	struct passwd *res;

	if (session->login == NULL) {
		send_reply(session->control.sock, FTP_SYNT_BAD_SEQ);
		return 1;
	}
	if (session->args == NULL) {
		send_reply(session->control.sock, FTP_SYNT_ERR);
		return 1;
	}
	pass = session->args;
	getpwnam_r(session->login, &(session->user), session->user_buf,
		sizeof(session->user_buf), &res);
	ft_memset(session->login, '\0', sizeof(session->login));
	if (res == NULL || res->pw_uid == 0) {
		send_reply(session->control.sock, FTP_AUTH_ERR);
		return 1;
	} else if (res->pw_uid == getuid()) {
		send_reply(session->control.sock, FTP_AUTH_OK);
		return 0;
	}
	printf("set user to %s\n", session->user.pw_name);
	if (write(session->pipefd, session, sizeof(*session))
		== sizeof(*session))
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
}
