;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_puts.s                                          :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:42:35 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 19:24:05 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_puts
extern ft_strlen
	
section .text
ft_puts:
	push	rbp
	mov	rbp, rsp
	test	rdi, rdi
	je	null_arg
	push	rdi
	call	ft_strlen
	mov	rdx, rax
	mov	rax, 0x2000004
	mov	rdi, 0x1
	pop	rsi
	syscall
	mov	rax, 0x2000004
	mov	rdi, 0x1
	lea	rsi, [rel nl]
	mov	rdx, 0x1
	syscall
	leave
	ret
null_arg:
	mov	rax, 0x2000004
	mov	rdi, 0x1
	lea	rsi, [rel null]
	mov	rdx, null.len
	syscall
	leave
	ret

section	.rodata
null:
	db "(null)", 0xa
.len: equ $ - null
nl:
	db 0xa
