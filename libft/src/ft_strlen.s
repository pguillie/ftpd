;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strlen.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:50:10 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:50:18 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_strlen

section .text
ft_strlen:
	push	rbp
	mov	rbp, rsp
	push	rdi
	xor	al, al
	mov	rcx, -0x1
	repne scasb
	dec	rdi
	mov	rax, rdi
	pop	rdi
	sub	rax, rdi
	leave
	ret
