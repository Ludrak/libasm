
;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_write.s                                   :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

;   Linux
%ifidn __OUTPUT_FORMAT__, elf64
	%assign W_CALL_x64  0x1
	%define ERRNO_LOC		__errno_location
	; wrt ..plt = with reference to [..]procedure linkage table
	%define REF_LNK_TABLE	wrt ..plt
	%macro JERRNO 1
		mov		rdx, rax
		neg		rdx
		test	rax, rax
		js		%1
	%endmacro

;   Darwin
%elifidn __OUTPUT_FORMAT__, macho64
	%assign W_CALL_x64  0x2000004
	%define ERRNO		__error
	; Useless for darwin but still needs to be defined
	%define	REF_LNK_TABLE
	%macro JERRNO 1
		mov		rdx, rax
		jc		%1
	%endmacro
%endif


;   WRITE - text section
	section	.text


	global	ft_write
	extern	ERRNO

ft_write:
	mov		rax, W_CALL_x64
	syscall
	JERRNO	.errno

;   ERRNO catch
.errno:
	sub		rsp, 8
	call	ERRNO REF_LNK_TABLE
	add		rsp, 8
	mov		[rax], rdx
	mov		rax, -1
	ret
