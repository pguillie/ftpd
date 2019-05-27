;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_memset.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:42:12 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:42:59 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_memset

section .text
ft_memset:
	push	rbp
	mov	rbp, rsp
	push	rdi
	mov	rcx, rdx
	mov	rax, rsi
	rep stosb
	pop	rax
	leave
	ret
