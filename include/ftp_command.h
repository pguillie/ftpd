/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_command.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:28:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/06/23 13:19:30 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_COMMAND_H
# define FTP_COMMAND_H

/* ACCESS CONTROL COMMANDS */

int user_name(char *arguments);
int change_working_directory(char *arguments);
int logout(char *arguments);

/* TRANSFER PARAMETER COMMANDS */

int data_port(char *arguments);
int representation_type(char *arguments);

/* FTP SERVICE COMMANDS */

int retrieve(char *arguments);
int store(char *arguments);
int print_working_directory(char *arguments);
int list(char *arguments);
int system_type(char *arguments);
int noop(char *arguments);

#endif /* FTP_COMMAND_H */
