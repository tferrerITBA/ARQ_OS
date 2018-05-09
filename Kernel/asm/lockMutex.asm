/*
section .text
global lockMutexAndShowPrevMutex

lockMutexAndShowPrevMutex:
	push rbp
	mov rbp, rsp
	mov rax, [rdi]	; rdi is the mutex address
	dec rax		; new mutex value after locking (mutex-1)
	xchg [rdi], rax

_exit:
	mov rsp, rbp
	pop rbp
	ret		; returns
*/
