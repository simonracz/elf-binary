global _start

section .data
message: db 'Hello!', 10

section .text
_start:
	mov rax, 1		; 1 == write syscall
	mov rdi, 1		; file descriptor = stdout == 1
	mov rsi, message	; address of bytes to write
	mov rdx, 7		; how many bytes?
	syscall
	mov rax, 60		; 60 == exit syscall
	xor rdi, rdi		; rdi = 0
	syscall	

; Syscall number : rax 
; up to 6 arguments
; rdi, rsi, rdx, r10, r8, r9
; rax
