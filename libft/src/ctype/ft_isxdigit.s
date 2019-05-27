;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isxdigit.s                                      :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:56:44 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:56:56 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_isxdigit
extern ft_ctype

section .text
ft_isxdigit:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x0
	call	ft_ctype
	leave
	ret
