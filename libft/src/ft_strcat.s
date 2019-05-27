;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_strcat.s                                        :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:39:04 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:50:02 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_strcat

section .text
ft_strcat:
	push	rbp
	mov	rbp, rsp
	mov	rax, rdi
	xor	rcx, rcx
offset:
	mov	dl, BYTE [rdi]
	test	dl, dl
	je	copy
	inc	rdi
	jmp	offset
copy:
	mov	dl, BYTE [rsi + rcx]
	mov	BYTE [rdi], dl
	test	dl, dl
	je	return
	inc	rdi
	inc	rcx
	jmp	copy
return:
	leave
	ret
