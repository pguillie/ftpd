;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_ispunct.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:55:16 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:55:31 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_ispunct
extern ft_ctype

section .text
ft_ispunct:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x6
	call	ft_ctype
	leave
	ret
