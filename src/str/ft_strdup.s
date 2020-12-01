;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_strdup.s                                  :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

;	Linux
%ifidn	__OUTPUT_FORMAT__, elf64
	%macro JMALLOC 1
		call %1 wrt ..plt
	%endmacro

;	Darwin
%elifidn __OUTPUT_FORMAT__, macho64
	%macro JMALLOC 1
		call %1
	%endmacro
%endif

;	STRDUP - text section
	section	.text
	global	ft_strdup

;	DEPENDENCIES
	extern	malloc
	extern	ft_strlen
	extern	ft_strncpy


;	char	*ft_strdup(char *s)
ft_strdup:	;rdi
	push	rdi		;save src
	call	ft_strlen	;call strlen
	inc		rax			;increment for \0
	mov		rdi, rax	;save size in rdi
	push	rax			;save size
	sub		rsp, 8
	JMALLOC	malloc		; call malloc
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







