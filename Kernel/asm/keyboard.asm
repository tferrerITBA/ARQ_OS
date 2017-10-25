section .text
global read_key

read_key:
		xor rax, rax
		in al, 64h
		and al, 0x01
		cmp al, 0x01
		jne no_data
		in al, 60h
		ret

no_data:
		mov rax, 0
		ret