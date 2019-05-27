;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isdigit.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:53:52 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:54:05 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_isdigit
extern ft_ctype

section .text
ft_isdigit:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x1
	call	ft_ctype
	leave
	ret
