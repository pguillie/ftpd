;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_tolower.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:50:49 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 20:00:34 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_tolower
extern ft_isupper

section .text
ft_tolower:
	push	rbp
	mov	rbp, rsp
	push	rdi
	call	ft_isupper
	pop	rdi
	test	rax, rax
	je	return
	or	rdi, 0x20
return:
	mov	rax, rdi
	leave
	ret
