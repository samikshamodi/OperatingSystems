all: 
	gcc -c prog-add.c 
	nasm -f elf64 add.asm 
	gcc -no-pie -o sum prog-add.o add.o 
	./sum
	

clean: 
	rm *.o sum
