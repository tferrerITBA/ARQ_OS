GLOBAL scanChar
GLOBAL printNChars


section .text

printNChars: ;ssize_t write(int fd, const void *buf, size_t count)
	
					
	enter	

	mov rax, 4		;syscall write
	mov rcx, rdi 	;puntero al string
	mov rdx, rsi	;cantidad de caracteres a imprimir
	mov rbx, 1		;std
	
	int 80h

	leave

	ret

scanChar:	;ssize_t read(int fd, void *buf, size_t count)
	
	enter

	mov rax, 3		;syscall read
	mov rcx, rdi	;puntero al buffer donde se guardaran los chars
	mov rdx, rsi	;cantidad de caracteres a leer
	mov rbx, 1

	int 80h

	leave 

	ret
