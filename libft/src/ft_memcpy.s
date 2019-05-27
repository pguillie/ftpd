;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_memcpy.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:41:51 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:42:00 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_memcpy

section .text
ft_memcpy:
	push	rbp
	mov	rbp, rsp
	push	rdi
	mov	rcx, rdx
	and	rcx, -0x8
	shr	rcx, 0x3
	rep movsq
	mov	rcx, rdx
	and	rcx, 0x7
	rep movsb
	pop	rax
	leave
	ret
