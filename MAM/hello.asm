section .data
	hello:     db 'Hello, World!',10    ; 'Hello, World!' plus a linefeed character
	helloLen:  equ $-hello             ; Length of the 'Hello world!' string

_start:
	mov RAX,4            ; The system call for write (sys_write)
	mov RDI,1            ; File descriptor 1 - standard output
	mov RSI,hello        ; Put the offset of hello in ecx
	mov RDX,helloLen     ; helloLen is a constant, so we don't need to say
	                     ;  mov edx,[helloLen] to get it's actual value
	int 80h              ; Call the kernel
	mov eax,1            ; The system call for exit (sys_exit)
	mov ebx,0            ; Exit with return "code" of 0 (no error)
	int 80h;