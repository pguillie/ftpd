;******************************************************************************;
;                                                                              ;
;                                                         :::      ::::::::    ;
;    ft_ctype.s                                         :+:      :+:    :+:    ;
;                                                     +:+ +:+         +:+      ;
;    By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+         ;
;                                                 +#+#+#+#+#+   +#+            ;
;    Created: 2019/02/21 18:51:23 by pguillie          #+#    #+#              ;
;    Updated: 2019/02/21 18:51:44 by pguillie         ###   ########.fr        ;
;                                                                              ;
;******************************************************************************;

global ft_ctype
extern ft_isascii

section .text
ft_ctype:
	push	rbp
	mov	rbp, rsp
	push	rdi
	call	ft_isascii
	test	rax, rax
	je	return
	pop	rdi
	lea	rax, [rel ascii]
	mov	rax, [rax + rdi * 0x2]
	and	rax, rsi
return:
	leave
	ret

section .rodata
ascii:
; bit position:
; cntrl space blank print graph punct alnum alpha upper lower digit xdigit
	dw 0b100000000000 ;   	NUL	cntrl
	dw 0b100000000000 ;   	SOH	cntrl
	dw 0b100000000000 ;   	STX	cntrl
	dw 0b100000000000 ;   	ETX	cntrl
	dw 0b100000000000 ;   	EOT	cntrl
	dw 0b100000000000 ;   	ENQ	cntrl
	dw 0b100000000000 ;   	ACK	cntrl
	dw 0b100000000000 ;   	BEL	cntrl
	dw 0b100000000000 ;   	BS	cntrl
	dw 0b111000000000 ;   	HT	cntrl|space|blank
	dw 0b110000000000 ;   	LF	cntrl|space
	dw 0b110000000000 ;   	VT	cntrl|space
	dw 0b110000000000 ;   	FF	cntrl|space
	dw 0b110000000000 ;   	CR	cntrl|space
	dw 0b100000000000 ;   	SO	cntrl
	dw 0b100000000000 ;   	SI	cntrl
	dw 0b100000000000 ;   	DLE	cntrl
	dw 0b100000000000 ;   	DC1	cntrl
	dw 0b100000000000 ;   	DC2	cntrl
	dw 0b100000000000 ;   	DC3	cntrl
	dw 0b100000000000 ;   	DC4	cntrl
	dw 0b100000000000 ;   	NAK	cntrl
	dw 0b100000000000 ;   	SYN	cntrl
	dw 0b100000000000 ;   	ETB	cntrl
	dw 0b100000000000 ;   	CAN	cntrl
	dw 0b100000000000 ;   	EM	cntrl
	dw 0b100000000000 ;   	SUB	cntrl
	dw 0b100000000000 ;   	ESC	cntrl
	dw 0b100000000000 ;   	FS	cntrl
	dw 0b100000000000 ;   	GS	cntrl
	dw 0b100000000000 ;   	RS	cntrl
	dw 0b100000000000 ;   	US	cntrl
	dw 0b011100000000 ;   	SPACE	print|space|blank
	dw 0b000111000000 ;   	!	print|graph|punct
	dw 0b000111000000 ;   	"	print|graph|punct
	dw 0b000111000000 ;   	#	print|graph|punct
	dw 0b000111000000 ;   	$	print|graph|punct
	dw 0b000111000000 ;   	%	print|graph|punct
	dw 0b000111000000 ;   	&	print|graph|punct
	dw 0b000111000000 ;   	'	print|graph|punct
	dw 0b000111000000 ;   	(	print|graph|punct
	dw 0b000111000000 ;   	)	print|graph|punct
	dw 0b000111000000 ;   	*	print|graph|punct
	dw 0b000111000000 ;   	+	print|graph|punct
	dw 0b000111000000 ;   	,	print|graph|punct
	dw 0b000111000000 ;   	-	print|graph|punct
	dw 0b000111000000 ;   	.	print|graph|punct
	dw 0b000111000000 ;   	/	print|graph|punct
	dw 0b000110100011 ;   	0	print|graph|alnum|digit|xdigit
	dw 0b000110100011 ;   	1	print|graph|alnum|digit|xdigit
	dw 0b000110100011 ;   	2	print|graph|alnum|digit|xdigit
	dw 0b000110100011 ;   	3	print|graph|alnum|digit|xdigit
	dw 0b000110100011 ;   	4	print|graph|alnum|digit|xdigit
	dw 0b000110100011 ;   	5	print|graph|alnum|digit|xdigit
	dw 0b000110100011 ;   	6	print|graph|alnum|digit|xdigit
	dw 0b000110100011 ;   	7	print|graph|alnum|digit|xdigit
	dw 0b000110100011 ;   	8	print|graph|alnum|digit|xdigit
	dw 0b000110100011 ;   	9	print|graph|alnum|digit|xdigit
	dw 0b000111000000 ;   	:	print|graph|punct
	dw 0b000111000000 ;   	;	print|graph|punct
	dw 0b000111000000 ;   	<	print|graph|punct
	dw 0b000111000000 ;   	=	print|graph|punct
	dw 0b000111000000 ;   	>	print|graph|punct
	dw 0b000111000000 ;   	?	print|graph|punct
	dw 0b000111000000 ;   	@	print|graph|punct
	dw 0b000110111001 ;   	A	print|graph|alnum|alpha|upper|xdigit
	dw 0b000110111001 ;   	B	print|graph|alnum|alpha|upper|xdigit
	dw 0b000110111001 ;   	C	print|graph|alnum|alpha|upper|xdigit
	dw 0b000110111001 ;   	D	print|graph|alnum|alpha|upper|xdigit
	dw 0b000110111001 ;   	E	print|graph|alnum|alpha|upper|xdigit
	dw 0b000110111001 ;   	F	print|graph|alnum|alpha|upper|xdigit
	dw 0b000110111000 ;   	G	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	H	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	I	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	J	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	K	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	L	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	M	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	N	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	O	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	P	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	Q	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	R	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	S	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	T	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	U	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	V	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	W	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	X	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	Y	print|graph|alnum|alpha|upper
	dw 0b000110111000 ;   	Z	print|graph|alnum|alpha|upper
	dw 0b000111000000 ;   	[	print|graph|punct
	dw 0b000111000000 ;   	\	print|graph|punct
	dw 0b000111000000 ;   	]	print|graph|punct
	dw 0b000111000000 ;   	^	print|graph|punct
	dw 0b000111000000 ;   	_	print|graph|punct
	dw 0b000111000000 ;   	`	print|graph|punct
	dw 0b000110110101 ;   	a	print|graph|alnum|alpha|lower|xdigit
	dw 0b000110110101 ;   	b	print|graph|alnum|alpha|lower|xdigit
	dw 0b000110110101 ;   	c	print|graph|alnum|alpha|lower|xdigit
	dw 0b000110110101 ;   	d	print|graph|alnum|alpha|lower|xdigit
	dw 0b000110110101 ;   	e	print|graph|alnum|alpha|lower|xdigit
	dw 0b000110110101 ;   	f	print|graph|alnum|alpha|lower|xdigit
	dw 0b000110110100 ;   	g	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	h	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	i	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	j	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	k	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	l	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	m	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	n	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	o	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	p	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	q	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	r	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	s	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	t	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	u	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	v	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	w	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	x	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	y	print|graph|alnum|alpha|lower
	dw 0b000110110100 ;   	z	print|graph|alnum|alpha|lower
	dw 0b000111000000 ;   	{	print|graph|punct
	dw 0b000111000000 ;   	|	print|graph|punct
	dw 0b000111000000 ;   	}	print|graph|punct
	dw 0b000111000000 ;   	~	print|graph|punct
	dw 0b100000000000 ;   	DEL	cntrl
