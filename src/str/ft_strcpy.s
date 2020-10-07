;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_strcpy.s                                  :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

	section .text
	global  ft_strcpy

	extern  ft_strlen
	extern	ft_strncpy
ft_strcpy:  ;rdi rsi
	push	rdi
	mov		rdi, rsi
	call	ft_strlen
	pop		rdi
	mov		rdx, rax
	inc		rdx
	sub		rsp, 8  ;align stack
	call	ft_strncpy
	add		rsp, 8	;restore stack
	ret

