;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_memcmp.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/03/01 15:07:32 by pguillie          #+#    #+#              ;
;    Updated: 2019/03/02 21:48:35 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_memcmp

section .text
ft_memcmp:
	push	rbp
	mov	rbp, rsp
	xor	rax, rax
	mov	rcx, rdx
	shr	rcx, 3
	repe
	cmpsq
	jne	diffq
	mov	rcx, rdx
	and	rcx, 0x0f
	repe
	cmpsb
	jne	diffb
	leave
	ret
diffq:
	
diffb:
	mov	dl, byte [rdi - 1]
	mov	cl, byte [rsi - 1]
	mov	rax, rdx
	sub	rax, rcx
	leave
	ret

; 	mov	rcx, rdx
; 	xor	rax, rax
; 	repz cmpsb
; 	jz	return
; 	xor	rdx, rdx
; 	mov	dl, byte [rdi - 1]
; 	xor	rcx, rcx
; 	mov	cl, byte [rsi - 1]
; 	mov	rax, rdx
; 	sub	rax, rcx
; return:
; 	leave
; 	ret
