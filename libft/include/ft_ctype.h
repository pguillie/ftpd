/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 09:22:32 by pguillie          #+#    #+#             */
/*   Updated: 2019/02/13 22:13:13 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CTYPE_H
# define FT_CTYPE_H

/*
 * Public
 */

int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isascii(int c);
int ft_isblank(int c);
int ft_iscntrl(int c);
int ft_isdigit(int c);
int ft_isgraph(int c);
int ft_islower(int c);
int ft_isprint(int c);
int ft_ispunct(int c);
int ft_isspace(int c);
int ft_isupper(int c);
int ft_isxdigit(int c);

/*
 * Private
 */

int ft_ctype(int c, int class);

#endif /* FT_CTYPE_H */
