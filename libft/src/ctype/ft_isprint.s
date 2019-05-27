;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isprint.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:54:52 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:55:02 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_isprint
extern ft_ctype

section .text
ft_isprint:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x8
	call	ft_ctype
	leave
	ret
