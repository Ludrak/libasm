;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_list_push_front.s                         :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

;   LIST_PUSH_FRONT - text section
	section	.text
	global	ft_list_push_front

;	DEPENDENCIES
	extern	malloc

ft_list_push_front:	; RDI(alst) RSI(lst)
	push	rsi
	push	qword [rdi]	;push as qword, popped in r10
	mov		rdi, 16		;sizeof(t_list) for malloc
	sub		rsp, 8
	call	malloc wrt ..plt
	add		rsp, 8
	test	rax, rax
	jz		.end
	pop		r10			;popped (qword)rdi
	pop		rsi
 .end:
	ret
