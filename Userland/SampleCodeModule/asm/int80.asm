GLOBAL timeInt     ; (edi, esi, edx, ecx)
GLOBAL printStr
GLOBAL readStr
GLOBAL clearScr
GLOBAL changeBColors
GLOBAL changeCColors
GLOBAL pixelInt
GLOBAL newProcess
GLOBAL psint
GLOBAL consumeInt
GLOBAL produceInt
GLOBAL initializeProdConsInt
GLOBAL kill
GLOBAL getpid
GLOBAL malloc
GLOBAL free

section .text

changeBColors:
	mov rbx, 0
	jmp changeColors

changeCColors:
	mov rbx, 1


readStr:
	mov rax, 3
	mov rbx, 1
	mov rcx, rdi
	mov rdx, 1
	int 0x80
	ret

clearScr:
	mov rax, 4
	mov rbx, 0
	int 0x80
	ret

printStr:
	mov rax, 4
	mov rbx, 1
	mov rcx, rdi
	mov rdx, rsi
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

changeColors:
	mov rax, 6
	mov rcx, rdi
	int 0x80
	ret

getpid:
	mov rax, 7
	int 0x80
	ret

newProcess:
	mov rax, 8
	mov rbx, rdi
	int 0x80
	ret

psint:
	mov rax, 9
	int 0x80
	ret

produceInt:
	mov rax, 10
	int 0x80
	ret

consumeInt:
	mov rax, 11
	int 0x80
	ret

kill:
	mov rax, 12
	mov rbx, rdi
	int 0x80
	ret

timeInt:
	mov rax, 13
	mov rcx, rdi
	int 0x80
	ret

malloc:
	mov rax, 14
	mov rbx, rdi
	int 0x80
	ret

free:
	mov rax, 15
	mov rbx, rdi
	int 0x80
	ret

initializeProdConsInt:
	mov rax, 16
	int 0x80
	ret
