;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_strcmp.s                                  :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

;	STRCMP - text section
	section	.text
	global	ft_strcmp

ft_strcmp:
;	Equal - loop until character is null or not equals eachother
.eq:
	mov		bl, [rsi]
	mov		al, [rdi]
	cmp		al, bl
	ja		.above
	jb		.below
	test	bl, al
	jz		.end
	inc		rsi
	inc		rdi
	jmp		.eq
;	Above - Called when str1 > str2
.above:
	sub		al, bl
	movzx	rax, al
	ret
;	Below - Called when str1 < str2
.below:
	sub		bl, al
	movzx	rax, bl
	neg		rax
	ret
;	End - Called when str1 or str2 is 0
.end:
	mov		rax, 0x0
	ret
