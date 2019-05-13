/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_command.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 12:28:24 by pguillie          #+#    #+#             */
/*   Updated: 2019/05/13 07:56:30 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_COMMAND_H
# define FTP_COMMAND_H

int user_name(int control_sock);
int print_working_directory(int control_sock);

#endif /* FTP_COMMAND_H */
