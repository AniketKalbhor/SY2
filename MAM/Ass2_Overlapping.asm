%macro println 2
	mov rax,01h
	mov rdi,01h
	mov rsi,%1
	mov rdx,%2
	syscall
%endmacro

printName:
    mov rax, 01h
    mov rdi, 01h
    mov rsi, name
    mov rdx, nameLength
    syscall      
    ret 

section .data
name db 'Aniket Kalbhor - 48'
nameLength equ $-name
msg0 db 10,'How Many Array Elements :'
len0 equ $-msg0

msg1 db 'Enter Array Elements :'
len1 equ $-msg1
msg2 db 10,'Before Transfer :'
len2 equ $-msg2
msg3 db 10,'Array is :'
len3 equ $-msg3
msg4 db 10,'After Transfer :'
len4 equ $-msg4

msg5 db 10,'Overlap Count :'
len5 equ $-msg5
space db ' '

section .bss
array resb 20
accept resb 3
display resb 2
cnt resb 1
ovcnt resb 1

section .text
	global _start

_start:
call printName

	println msg0,len0
	call acceptNo
	mov [cnt],bl

	println msg1,len1

	mov rsi,array
	mov cl,[cnt]

acceptNext:
	push rcx
	push rsi

	call acceptNo
	
	pop rsi
	pop rcx	


	mov [rsi],bl
	inc rsi
	dec cl
	jnz acceptNext


	println msg5,len5
	
	call acceptNo
	mov [ovcnt],bl



	println msg2,len2
	println msg3,len3

	mov rsi,array
	mov cl,20

dispNext:
	
	push rsi
	push rcx

	mov bl,[rsi]
	call displayNo	

	pop rcx
	pop rsi

	inc rsi
	dec cl
	jnz dispNext

	mov rdi,array
	mov rcx,00h
	mov cl,[cnt]
	add cl,cl
	sub cl,[ovcnt]
	add rdi,rcx
	dec rdi

	mov rcx,00h
	mov cl,[cnt]
	mov rsi,array
	add rsi,rcx
	dec rsi

;	std
;	rep movsb

movAgain:

	mov al,[rsi]
	mov [rdi],al
	dec rsi
	dec rdi
	dec  cl
	jnz movAgain
	

	println msg4,len4
	println msg3,len3

	mov rsi,array
	mov cl,20

dispNext1:
	
	push rsi
	push rcx

	mov bl,[rsi]
	call displayNo	

	pop rcx
	pop rsi

	inc rsi
	dec cl
	jnz dispNext1








	





	


















	mov rax,60
	syscall

acceptNo:
	mov rax,00h
	mov rdi,00h
	mov rsi,accept
	mov rdx,03h
	syscall

	mov al,[accept]
	sub al,30h
	cmp al,09h
	jle dontSub
	sub al,07h
dontSub:
	mov cl,04h
	shl al,cl
	mov bl,al

	mov al,[accept+1]
	sub al,30h
	cmp al,09h
	jle dontSubb
	sub al,07h
dontSubb:
	or bl,al

ret


displayNo:

	mov al,bl
	and al,0f0h
	mov cl,04h
	shr al,cl
	add al,30h
	cmp al,39h
	jle dontAdd
	add al,07h
dontAdd:

	mov [display],al

	mov al,bl
	and al,0fh
	add al,30h
	cmp al,39h
	jle dontAddd
	add al,07h
dontAddd:
	mov [display+1],al

	println display,02h
	println space,01h

ret















