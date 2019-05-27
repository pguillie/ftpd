;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_iscntrl.s                                       :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:53:32 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:53:43 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_iscntrl
extern ft_ctype

section .text
ft_iscntrl:
	push	rbp
	mov	rbp, rsp
	mov	rsi, 0x1
	shl	rsi, 0xb
	call	ft_ctype
	leave
	ret
