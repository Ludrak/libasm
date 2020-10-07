;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_strdup.s                                  :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

;	STRDUP - text section
	section	.text
	global	ft_strdup

;	DEPENDENCIES
	extern	malloc
	extern	ft_strlen
	extern	ft_strncpy

ft_strdup:	;rdi
	push	rdi		;save src
	call	ft_strlen	;call strlen
	inc		rax			;increment for \0
	mov		rdi, rax	;save size in rdi
	push	rax			;save size
	sub		rsp, 8
	call	malloc wrt ..plt		;call malloc
	add		rsp, 8
	pop		rdx			;set rdx to size
	pop		rsi			;set rsi to src
	test	rax, rax	;null check
	jz		.err
	mov		rdi, rax	;set rdi to dst
	sub		rsp, 8
	call	ft_strncpy
	add		rsp, 8
.err:
	ret

