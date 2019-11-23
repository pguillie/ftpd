/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:14:14 by pguillie          #+#    #+#             */
/*   Updated: 2019/11/23 12:47:43 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

int invocation(int argc, char *argv[], char **port);
int server(const char *service);
int run_service(const char *service);
int connection_manager(int lsoc);

#endif /* SERVER_H */
