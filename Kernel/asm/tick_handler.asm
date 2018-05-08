EXTERN schedule
EXTERN _cli
EXTERN _sti
EXTERN putnString
GLOBAL tick_handler

section .text

tick_handler:
		;PUSHAQ
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
		PUSH RSP
		PUSH RBP
		PUSH RAX
		PUSH RBX
		PUSH RCX
		PUSH RDX
		PUSH RSI
		PUSH RDI
%endmacro

%macro POPAQ 0
		POP RDI
		POP RSI
		POP RDX
		POP RCX
		POP RBX
		POP RAX
		POP RBP
		POP RSP
%endmacro

section .data
	cadena db "retorne",10
	longitud equ $-cadena
