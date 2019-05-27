;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_memchr.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/25 14:05:22 by pguillie          #+#    #+#              ;
;    Updated: 2019/03/02 21:15:39 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_memchr

section .text
ft_memchr:
	push	rbp
	mov	rbp, rsp
	mov	rcx, rdx
	mov	rax, rsi
	repne
	scasb
	jz	success
	xor	rax, rax
	leave
	ret
success:
	dec	rdi
	mov	rax, rdi
	leave
	ret
