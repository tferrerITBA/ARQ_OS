section .text
global read_key

read_key:
		xor rax, rax
		in al, 64h
		and al, 0xE1; and al, 0x01;          000xxxx1 (2 + 4 + 8, 8)  
		cmp al, 0x01;   hace falta verificar algun bit ademas del 0?
		jne no_data
		in al, 60h
		ret

no_data:
		xor rax, rax
		ret