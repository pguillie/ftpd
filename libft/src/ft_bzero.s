;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_bzero.s                                         :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:38:38 by pguillie          #+#    #+#              ;
;    Updated: 2019/03/02 20:37:42 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_bzero

section .text
ft_bzero:
	push	rbp
	mov	rbp, rsp
	mov	rcx, rsi
	and	rsi, -0x8
small:
	cmp	rcx, rsi
	jle	large
	dec	rcx
	mov	byte [rdi + rcx], 0x0
	jmp	small
large:
	test	rcx, rcx
	je	return
	sub	rcx, 0x8
	mov	qword [rdi + rcx], 0x0
	jmp	large
return:
	mov	rax, rdi
	leave
	ret
