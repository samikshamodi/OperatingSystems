;Name: Samiksha Modi
;Roll No:2019331

bits 16 				;so that nasm knows it is 16 bit code
org 0x7c00 				;nasm then outputs stuff present at the offset 0x7c00 
						;if the last two bytes of the first 512 bytes loaded into memory by the BIOS is 0xaa55 then the BIOS jumps to location 0x7c00 effectively transferring the control to the bootloader

enter_protected_mode:
	mov ax,0x3
	int 0x10 			;vga text mode is set to 3. vga is a simple way to print text to screen

	mov ax, 0x2401 		;We need to enable the A20 line so that we can access more than 1MB of memory
	int 0x15			;enables A20 bit

	cli					;clear interrupt flag. sets it to 0. maskable interrupts wont be handled
	lgdt [gdt_pointer] 	;to load the global desriptor table. the gdt has entries telling the cpu about memory segments
	mov eax, cr0 		;move contents of cr0 to eax register
	or eax,0x1 			;sets the protected mode bit on special cpu reg cr0, thereby enabling protected mode
	mov cr0,eax 		;move contents of eax to cr0
	jmp CODE_SEG: start_protected_mode 		;far jump to 32 bit code segment. so we need to change the memory segment. we change it to CODE_SEG 

gdt_null:
	dq 0x0

gdt_code:
	dw 0xFFFF 			;limit
	dw 0x0000			;base (low)
	db 0x00 			;base (middle) 
	db 10011010b 		;access byte
	db 11001111b 		;flags+upper limit
	db 0x00 			;base (high)

gdt_data:
	dw 0xFFFF			;limit
	dw 0x0000 			;base (low)
	db 0x00 			;base (middle)
	db 10010010b 		;access byte. we change the executable bit to 0 for data segment
	db 11001111b 		;flags+upper limit
	db 0x00 			;base (high)

gdt_end:

gdt_pointer:				;to load the above gdt we need a gdt pointer 
	dw gdt_end - gdt_null 	;gdt size
	dd gdt_null 			;points to the structure itself

CODE_SEG equ gdt_code - gdt_null 	;offsets into gdt
DATA_SEG equ gdt_data - gdt_null 	;offsets into gdt

bits 32				  	;so that nasm knows it is 32 bit code

start_protected_mode:
	;we first need to point our segment reigsters to the new data that we defined in gdt
	mov ax, DATA_SEG	;moving data segment value to ax
	mov ss, ax 			;making the remaining segement point to data segment
	mov ds, ax			;making the remaining segement point to data segment
	mov es, ax 			;making the remaining segement point to data segment
	mov fs, ax			;making the remaining segement point to data segment
	mov gs, ax 			;making the remaining segement point to data segment

	mov ebx, 0xb8000	;to print to screen we need to alter the video memory directly. video memory starts at 0xb8000 in text mode. text mode is where we are currently in 
	mov esi,hello 		;load address of hello into esi

.loop:					;function to write string to video memory
	lodsb				;loads byte at address in si into al and increments si
	cmp al,0 			;check if al==0
	je .register 			;if 0 then the string has been printed, go to halt
	or eax,0x0100 		;top byte defines character color, 1=blue
	mov word [ebx], ax  ;bottom byte defines ascii code point
	add ebx,2 			;a word is 2 bytes
	jmp .loop

.register:
	mov edx, cr0 		;move contents of cr0 register to edx
	mov ecx, 32 		;the cr0 register has 32 bits 


.loop2:
	mov eax, 0x130		;sets text to blue from black
	shl edx,1 			;left shift the value in edx register by 1 bit and put top bit in carry flag
	adc eax,0 			;determine if the lower byte is 0 or 1
	mov [ebx],ax 		;move what we need to print to this loccation
	add ebx,2 			;a word is 2 bytes
	dec ecx 			;dec ecx so that we only print the 32 bits 
	jnz .loop2

halt:
	cli					;clear interrupts
	hlt 				;halts execution

hello: db "Hello world! Contents of cr0 register->",0

times 510-($-$$) db 0	;padding the remaining 510 bytes with 0
dw 0xaa55				;marks this 512 byte sector as bootable. this is how our system knows that it is a bootloader

;The following sites were used to understand and write this program
;Link1: The bootloader code in my program can be found at http://3zanders.co.uk/2017/10/16/writing-a-bootloader2/
;Link2: The code to print the contents of the cr0 register in my program can be found at https://stackoverflow.com/questions/65361946/print-the-contents-of-the-cr0-register
;Link3: To understand what was happening in the Link1 code I watched this video multiple times https://www.youtube.com/watch?v=pXzortxPZR8 Moving Into 32-Bit Protected Mode | Make a 64 bit OS From Scratch!! | Part 4 by Poncho
;The comments in my program are there to explain my understanding of the code I took from the above links. Covered in the writeup in greater detail.
;Link4: To understand global descriptor table https://wiki.osdev.org/Global_Descriptor_Table 
;I do not claim to have come up with the bootloader code and the cr0 content printing code myself.I understood what was happening from the the above links and then implemented it on my own.
