;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strdup.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:48:53 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:49:35 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_strdup
extern malloc
extern ft_strlen, ft_memcpy

section .text
ft_strdup:
	push	rbp
	mov	rbp, rsp
	push	rdi
	call	ft_strlen
	mov	rdi, rax
	push	rdi
	call	malloc WRT ..plt
	test	rax, rax
	je	return
	pop	rdx
	pop	rsi
	mov	rdi, rax
	call	ft_memcpy
return:
	leave
	ret
