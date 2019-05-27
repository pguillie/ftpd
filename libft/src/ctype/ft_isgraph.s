;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_isgraph.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:54:12 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:54:29 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_isgraph
extern ft_ctype

section .text
ft_isgraph:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0x7
	call	ft_ctype
	leave
	ret
