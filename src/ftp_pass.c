/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_pass.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 08:38:36 by pguillie          #+#    #+#             */
/*   Updated: 2019/10/03 11:16:12 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* PASS is only handled after USER */

int ftp_pass(struct ftp_session *session)
{
	send_reply(session->control.sock, FTP_SYNT_BAD_SEQ);
	return 1;
}

/* #include <pwd.h> */
/* #include <shadow.h> */

/* int ftp_pass(struct ftp_session *session) */
/* { */
/* 	char *pass; */
/* 	struct passwd *pw; */
/* 	struct spwd * */

/* 	if (session->user.login == NULL) { */
/* 		send_reply(session->control.sock, FTP_SYNT_BAD_SEQ); */
/* 		return 1; */
/* 	} */
/* 	if (session->args == NULL) { */
/* 		send_reply(session->control.sock, FTP_SYNT_ERR); */
/* 		return 1; */
/* 	} */
/* 	pass = session->args; */




/* 	pw = getpwnam(username); */
/* 	if (pw == NULL) */
/* 		fatal("couldn't get password record"); */
/* 	spw = getspnam(username); */
/* 	if (spw == NULL && errno == EACCES) */
/* 		fatal("no permission to read shadow password file"); */

/* 	if (spw != NULL)           /\* If there is a shadow password record *\/ */
/* 		pw->pw_passwd = spw->sp_pwdp;     /\* Use the shadow password *\/ */

/* 	password = getpass("Password: "); */

/* 	/\* Encrypt password and erase cleartext version immediately *\/ */

/* 	encrypted = crypt(password, pw->pw_passwd); */
/* 	for (p = password; *p != '\0'; ) */
/* 		*p++ = '\0'; */

/* 	if (encrypted == NULL) */
/* 		errExit("crypt"); */

/* 	authOk = strcmp(encrypted, pw->pw_passwd) == 0; */
/* 	if (!authOk) { */
/* 		printf("Incorrect password\n"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */




/* 	getpwnam_r(session->login, &(session->user), session->user_buf, */
/* 		sizeof(session->user_buf), &res); */
/* 	ft_memset(session->login, '\0', sizeof(session->login)); */
/* 	if (res == NULL || res->pw_uid == 0) { */
/* 		send_reply(session->control.sock, FTP_AUTH_ERR); */
/* 		return 1; */
/* 	} else if (res->pw_uid == getuid()) { */
/* 		send_reply(session->control.sock, FTP_AUTH_OK); */
/* 		return 0; */
/* 	} */
/* 	printf("set user to %s\n", session->user.pw_name); */
/* 	if (write(session->pipefd, session, sizeof(*session)) */
/* 		== sizeof(*session)) */
/* 		exit(EXIT_SUCCESS); */
/* 	else */
/* 		exit(EXIT_FAILURE); */
/* } */
