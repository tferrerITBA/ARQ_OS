EXTERN schedule
EXTERN _cli
EXTERN _sti
EXTERN putnString
GLOBAL tick_handler

section .text

tick_handler:
		MOV RDI, RSP
		CALL schedule
		CMP RAX, 0
		JE cont_switch_end
		MOV RSP, RAX
cont_switch_end:
		mov rdi, cadena
        mov rsi, longitud
        call putnString
		RET

section .data
	cadena db "retorne",10
	longitud equ $-cadena
