GLOBAL timeInt     ; (edi, esi, edx, ecx)
GLOBAL printStr
GLOBAL readStr
GLOBAL clearScr
GLOBAL changeBColors
GLOBAL changeCColors
GLOBAL pixelInt
GLOBAL newProcessInt
GLOBAL psint
GLOBAL downInt
GLOBAL upInt
GLOBAL kill
GLOBAL getpid
GLOBAL malloc
GLOBAL free
GLOBAL realloc
GLOBAL calloc
GLOBAL initializeSemsAndMutexInt
GLOBAL send
GLOBAL receive
GLOBAL readPipe
GLOBAL writePipe
GLOBAL createPipe
GLOBAL openPipe
GLOBAL closePipe

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

newProcessInt:
	mov rax, 8
	mov rbx, rdi
	int 0x80
	ret

psint:
	mov rax, 9
	int 0x80
	ret

upInt:
	mov rax, 10
	mov rbx, rdi
	int 0x80
	ret

downInt:
	mov rax, 11
	mov rbx, rdi
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

initializeSemsAndMutexInt:
	mov rax, 16
	int 0x80
	ret

realloc:
	mov rax, 17
	mov rbx, rdi
	int 0x80
	ret

calloc:
	mov rax, 18
	mov rbx, rdi
	mov rcx, rsi
	int 0x80
	ret

send:
	mov rax, 19
	mov rbx, rdi
	int 0x80
	ret

receive:
	mov rax, 20
	int 0x80
	ret

readPipe:
	mov rax, 21
	mov rbx, rdi
	int 0x80
	ret

writePipe:
	mov rax, 22
	mov rbx, rdi 
	mov rcx, rsi
	int 0x80
	ret

createPipe:
	mov rax, 23
	int 0x80
	ret

openPipe:
	mov rax, 24
	mov rbx, rdi
	mov rcx, rsi
	int 0x80
	ret

//Meter aca syscalls de fs en orden numerico

closePipe:
	mov rax, 35
	mov rbx, rdi
	int 0x80
	ret
