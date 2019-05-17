/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_command.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:28:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/16 14:40:47 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_COMMAND_H
# define FTP_COMMAND_H

/* ACCESS CONTROL COMMANDS */

int user_name(int control_sock);
int change_working_directory(int control_sock);
int logout(int control_sock);

/* TRANSFER PARAMETER COMMANDS */

int data_port(int control_sock);

/* FTP SERVICE COMMANDS */

int retrieve(int control_sock);
int store(int control_sock);
int print_working_directory(int control_sock);
int list(int control_sock);
int system_type(int control_sock);

#endif /* FTP_COMMAND_H */
