;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isspace.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:55:42 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:56:19 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_isspace
extern ft_ctype

section .text
ft_isspace:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0xa
	call	ft_ctype
	leave
	ret
