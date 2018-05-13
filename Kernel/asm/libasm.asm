GLOBAL cpuVendor
GLOBAL getRSP
GLOBAL pushRegisters
GLOBAL popRegisters

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

getRSP:
	mov rax, rsp
	ret

pushRegisters:
	mov rcx, rsp ; guardo el valor original de rsp
	mov rsp, rdi ; cargo el valor de stack al que quiero pushear registros
	pushState ;pusheo los registros
	mov rax, rsp ;muevo el nuevo valor de stack pointer a rax
	mov rsp, rcx ;reestablezco el valor del stack cuando llegue
	ret

popRegisters:
	popState
	mov rax, rsp

%macro pushState 0
	push rbp
	push ss
	push rsp
	pushfq
	push cs
	push rip
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	push fs
	push gs
%endmacro

%macro popState 0
	pop gs
	pop fs
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
	pop rip
    pop cs
    popfq
    pop rsp
    pop ss
    pop rbp
%endmacro