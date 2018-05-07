GLOBAL cpuVendor
GLOBAL getRIP
GLOBAL getRSP

section .text

getRIP:
	mov rax, [rsp+12*8]
	ret

getRSP:
	mov rax, [rsp+11*8]
    ret

setRIP:
	mov [rsp+12*8], rdi
	ret
	
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
