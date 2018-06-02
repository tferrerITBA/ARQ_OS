GLOBAL cpuVendor
GLOBAL yield
EXTERN schedule

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

yield:
	pushState

	MOV RDI, RSP
    CALL schedule
    CMP RAX, 0
    JE cont_switch_end
    MOV RSP, RAX
cont_switch_end:
	popState
	ret
