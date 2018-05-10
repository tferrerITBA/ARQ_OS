
section .text
global lockSemAndShowPrevSem

lockSemAndShowPrevSem:
	push rbp
	mov rbp, rsp
	mov rax, [rdi]	; rdi is the sem address
	dec rax		; new sem value after locking (sem-1)
	xchg [rdi], rax

_exit:
	mov rsp, rbp
	pop rbp
	ret		; returns
