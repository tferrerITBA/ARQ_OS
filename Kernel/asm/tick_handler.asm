tick_handler:
		PUSHAQ
		CALL schedule
		CMP RAX, 0
		JE cont_switch_end
		MOV RSP, RAX
cont_switch_end:
		POPAQ
		MOV AL, 20h
        OUT 20h, AL
		IRETQ

%macro PUSHAQ 0
		PUSH RSP
		PUSH RBP
		PUSH RAX
		PUSH RBX
		PUSH RCX
		PUSH RDX
		PUSH RSI
		PUSH RDI
		PUSHFQ
%endmacro

%macro POPAQ 0
		POPFQ
		POP RDI
		POP RSI
		POP RDX
		POP RCX
		POP RBX
		POP RAX
		POP RBP
		POP RSP
%endmacro
