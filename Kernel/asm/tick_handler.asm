EXTERN schedule
EXTERN _cli
EXTERN _sti
EXTERN putnString
GLOBAL tick_handler

section .text

tick_handler:
		;PUSHAQ
		MOV RDI, RSP
		CALL schedule
		CMP RAX, 0
		JE cont_switch_end
		MOV RSP, RAX
cont_switch_end:
		;POPAQ
		;MOV AL, 20h
        ;OUT 20h, AL
        ;mov rdi, cadena
        ;mov rsi, longitud
        ;call putnString
		RET

%macro PUSHAQ 0
		push rax
        push rbx
        push rcx
        push rdx
        push rbp
        push rdi
        push rsi
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
%endmacro

%macro POPAQ 0
		pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rsi
        pop rdi
        pop rbp
        pop rdx
        pop rcx
        pop rbx
        pop rax
%endmacro

section .data
	cadena db "retorne",10
	longitud equ $-cadena
