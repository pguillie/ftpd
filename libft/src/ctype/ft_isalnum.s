;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isalnum.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:52:26 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:52:37 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_isalnum
extern ft_ctype

section .text
ft_isalnum:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x5
	call	ft_ctype
	leave
	ret
