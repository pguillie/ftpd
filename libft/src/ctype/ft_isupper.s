;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isupper.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:56:27 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:56:38 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_isupper
extern ft_ctype

section .text
ft_isupper:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x3
	call	ft_ctype
	leave
	ret
