;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_islower.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:54:36 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:54:47 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_islower
extern ft_ctype

section .text
ft_islower:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x2
	call	ft_ctype
	leave
	ret
