;  -----------------------------------------------------------------
;                                                 :::      ::::::::
;  ft_read.s                                    :+:      :+:    :+:
;                                             +:+ +:+         +:+
;  By: lrobino <lrobino@student.42.fr>      +#+  +:+       +#+
;                                         +#+#+#+#+#+   +#+
;                                              #+#    #+#
;                                             ###   ########Lyon.fr
;  -----------------------------------------------------------------

;   Linux
%ifidn __OUTPUT_FORMAT__, elf64
	%assign R_CALL_x64  0x0
	%define ERRNO_LOC	__errno_location
	; PIC relocation for ELF needs ..plt
	%define ERRNO_CALLW	wrt ..plt
	%macro JERRNO 1
		mov		rdx, rax
		neg		rdx
		test	rax, rax
		js		%1
	%endmacro

;   Darwin
%elifidn __OUTPUT_FORMAT__, macho64
	%assign R_CALL_x64  0x2000003
	%define ERRNO_LOC	__error
	%define ERRNO_CALLW
	%macro JERRNO 1
		mov		rdx, rax
		jc		%1
	%endmacro
%endif


;   READ - text section
	section	.text

	global	ft_read
	extern	ERRNO_LOC

ft_read:
	mov		rax,	R_CALL_x64
	syscall
	JERRNO	.errno
	ret
;   ERRNO catch
.errno:
	sub		rsp,	8
	call	ERRNO_LOC ERRNO_CALLW
	add		rsp,	8
	mov		[rax],	rdx
	mov		rax,	-1
	ret
