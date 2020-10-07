;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_strlen.s                                  :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

;	STRLEN - text section
	section .text
	global  ft_strlen 

ft_strlen:
	mov		rax, rdi
	cmp		byte [rdi], 0
	je		.end
;	Increment until rax = null
.inc:
	inc		rax
	cmp		byte [rax], 0
	jne		.inc
;	End of string, sub registers for len.
.end:
	sub		rax, rdi
	ret