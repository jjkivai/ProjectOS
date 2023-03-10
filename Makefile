# $@ = target file
# $< = first dependency
# $^ = all dependencies

C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJ_FILES = ${C_SOURCES:.c=.o}

all: run

kernel.bin: boot/kernel_entry.o kernel.o #${OBJ_FILES}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

os_image.bin: boot/MBR.bin kernel.bin
	cat $^ > $@

run: os_image.bin 
	qemu-system-i386 -drive format=raw,file=$<,index=0,if=floppy


%.bin: %.asm
	nasm $< -f bin -o $@ 

%.o: %.c #${HEADERS}
	gcc -m32 -ffreestanding -fno-pie -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@
