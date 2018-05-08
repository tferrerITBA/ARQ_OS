GLOBAL timeInt     ; (edi, esi, edx, ecx)
GLOBAL printStr
GLOBAL readStr
GLOBAL clearScr
GLOBAL changeBColors
GLOBAL changeCColors
GLOBAL pixelInt
GLOBAL fork

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

clearScr:
	mov rax, 4
	mov rbx, 0
	int 0x80
	ret



changeBColors:
	mov rbx, 0
	jmp changeColors

changeCColors:
	mov rbx, 1

changeColors:
	mov rax, 6
	mov rcx, rdi
	int 0x80
	ret

pixelInt:
	mov rax, 5
	xor rcx, rcx
	xor rdx, rdx
	mov rcx, rdi
	mov rdx, rsi
	int 0x80
	ret

readStr:
	mov rax, 3
	mov rbx, 1
	mov rcx, rdi
	mov rdx, 1
	int 0x80
	ret

fork:
	mov rax, 2
	int 0x80
	ret