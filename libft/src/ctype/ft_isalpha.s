;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isalpha.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:52:44 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:52:53 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_isalpha
extern ft_ctype

section .text
ft_isalpha:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x4
	call	ft_ctype
	leave
	ret
