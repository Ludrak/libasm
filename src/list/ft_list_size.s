;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_list_size.s                               :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

;   LIST_SIZE - text section
	section	.text
	global	ft_list_size

ft_list_size: ; rdi
	mov	rax, 0x0
.next:
	cmp	[rdi + 8], dword 0x0
	je	.end
	inc	rax
	mov	dword rdi, [rdi + 8]
	jmp	.next
.end:
	ret