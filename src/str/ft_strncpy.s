;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_strncpy.s                                 :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

;	STRNCPY - text section
	section .text
	global  ft_strncpy

;	char	*ft_strncpy(char const *dst, char const *src, size_t n)
ft_strncpy:
	mov		rax, rdi
	mov		rcx, rdx
	cld				; clear direction flag
	rep		movsb	; copy rcx bytes from rsi to rdi
	ret

