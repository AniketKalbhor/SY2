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

msg1 	db 10,'Menu: '
     	db 10,'1.S Addition'
 	db 10,'2.A & S'
	db 10,'3. exit'
	db 10,'Choice :'  	
len1 equ $-msg1

msg2 db 10,'Enter Multiplicand : '
len2 equ $-msg2
msg3 db 10,'Enter Multiplier :'
len3 equ $-msg3
msg4 db 10,'Product is :'
len4 equ $-msg4


section .bss
mulr resb 1
muld resb 1
result resb 2

accept resb 3
display resb 2
choice resb 2

section .text
	global _start

_start:
call printName
menuAgain:
	println msg1,len1

	mov rax,00h
	mov rdi,00h
	mov rsi,choice
	mov rdx,02h
	syscall
	
	mov al,[choice]

	cmp al,31h
	jne next

	call SAddition
	jmp menuAgain
next:
	cmp al,32h
	jne next1
	call AddShift
	jmp menuAgain

next1:

	cmp al,33h
	je exit
	jmp menuAgain

exit:
	mov rax,60
	syscall


SAddition:
	println msg2,len2
	call acceptNo
	mov [muld],bl

	println msg3,len3
	call acceptNo
	mov [mulr],bl

	mov dx,0000h
	mov cl,[mulr]
	mov bl,[muld]
	mov bh,00h
addNext:
	add dx,bx
	dec cl
	jnz addNext

	mov [result],dx

	
	println msg4,len4

	mov bl,[result+1]
	call displayNo
	mov bl,[result]
	call displayNo



ret

AddShift:
	println msg2,len2
	call acceptNo
	mov [muld],bl

	println msg3,len3
	call acceptNo
	mov [mulr],bl

	mov al,[mulr]
	mov cl,08h
	mov bl,[muld]
	mov bh,00h
	mov dx,0000h

chkNextBit:

	shr al,01h
	jnc onlyShift

	add dx,bx
onlyShift:
	shl bx,01h
	dec cl
	jnz chkNextBit


	mov [result],dx

	
	println msg4,len4

	mov bl,[result+1]
	call displayNo
	mov bl,[result]
	call displayNo

ret



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
ret
