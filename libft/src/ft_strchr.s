;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strchr.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:57:16 by pguillie          #+#    #+#              ;
;    Updated: 2019/03/01 15:02:33 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_strchr
extern ft_strlen

section .text
ft_strchr:
	push	rbp
	mov	rbp, rsp
	push	rdi
	call	ft_strlen
	mov	rcx, rax
	mov	rax, rsi
	pop	rdi
	test	rcx, rcx
	jz	endofstr
	repne scasb
	jnz	endofstr
	dec	rdi
success:
	mov	rax, rdi
	leave
	ret
endofstr:
	cmp	al, 0x0
	je	success
	xor	rax, rax
	leave
	ret
