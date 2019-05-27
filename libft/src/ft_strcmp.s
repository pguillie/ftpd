;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strcmp.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/03/01 18:59:14 by pguillie          #+#    #+#              ;
;    Updated: 2019/03/02 17:55:17 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_strcmp

section .text
ft_strcmp:
	push	rbp
	mov	rbp, rsp
	xor	rax, rax
iter:
	mov	al, byte [rdi]
	test	al, al
	jz	diff
	cmp	al, byte [rsi]
	jne	diff
	inc	rdi
	inc	rsi
	jmp	iter
diff:
	movzx	rdx, byte [rsi]
	sub	rax, rdx
	leave
	ret
