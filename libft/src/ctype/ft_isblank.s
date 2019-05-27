;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isblank.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:53:18 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:53:26 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_isblank
extern ft_ctype

section .text
ft_isblank:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x9
	call	ft_ctype
	leave
	ret
