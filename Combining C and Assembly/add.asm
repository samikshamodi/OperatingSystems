section .data
    hyphen: db "-"
    hyphenlen: equ $-hyphen
    newline: db "",10
    newlinelen: equ $-newline

section .text
    global add

add:
     	mov rax, rdi
    	mov rbx, rsi
    	add rax, rbx
    
    	cmp rax,0
    	jge _print
    	
    	;the value stored in rax is negative   	
    	push rax
    	
    	;syscall to print hyphen
    	mov rax, 1
    	mov rdi, 1
    	mov rsi, hyphen
    	mov rdx, hyphenlen
    	syscall
    	
    	pop rax
    	neg rax	
    
_print:
    	;printing the sum which is stored in the rax register
    	call _printAns
    	
    	mov rax, 1
    	mov rdi, 1
    	mov rsi, newline
    	mov rdx, newlinelen
    	syscall
	
    	;exit system call
    	mov rax, 60
    	mov rdi,0
    	syscall

_printAns:
	mov rbx, 10
	mov rcx, 0 ;setting counter to 0
	
_loop1:
	mov rdx, 0
	div rbx
	push rdx	;push remainder on stack
	inc rcx
		 
    	cmp rax, 0
    	jne _loop1
 
_loop2:
      	pop rax
      	add rax,48	;converting to character
      	push rcx	;store counter
      	push rax	;push character to stack
      	mov rcx,rsp	;make rcx point to it
      	      	
      	mov rax, 1
    	mov rdi, 1
    	mov rsi, rcx
    	mov rdx, 1
    	syscall
    	
    	pop rax	;remove the character after printing
    	pop rcx	;get counter
    	dec rcx	;decrease counter
      	
      
      	cmp rcx,0
      	jne _loop2 
 
    	ret
    
	
	
