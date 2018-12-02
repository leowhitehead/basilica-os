CC = i686-elf-gcc

main: kernel.c linker.ld boot.asm
	nasm -felf32 boot.asm -o boot.o
	$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CC) -T linker.ld -o basilica.bin -ffreestanding -nostdlib -O2 boot.o kernel.o -lgcc
	cp basilica.bin isodir/boot/basilica.bin
	grub-mkrescue -o basilica.iso isodir

clean:
	rm ./*.o ./*.bin ./*.iso ./isodir/boot/*.bin