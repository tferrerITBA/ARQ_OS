GLOBAL timeInt     ; (edi, esi, edx, ecx)
GLOBAL printStr

section .text

timeInt:
	mov rax, 13
	mov rcx, rdi
	int 0x80
	ret

printStr:
	mov rax, 4
	mov rbx, 1
	mov rcx, rdi
	mov rdx, rsi
	int 0x80
	ret