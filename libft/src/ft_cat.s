;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_cat.s                                           :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:39:20 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:44:21 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_cat

%define buf_size 0x1000
	
section .text
ft_cat:
	push	rbp
	mov	rbp, rsp
	lea	rsi, [rel buf]
rw:
	mov	rax, 0x2000003
	mov	rdx, buf_size
	syscall
	jc	return
	test	rax, rax
	je	return
	mov	rdx, rax
	mov	rax, 0x2000004
	push	rdi
	mov	rdi, 0x1
	syscall
	jc	return
	pop	rdi
	jmp	rw
return:
	leave
	ret	

section	.bss
buf:
	resb buf_size
