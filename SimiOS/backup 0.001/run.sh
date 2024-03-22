nasm -f elf32 kernel.asm -o out/kernelasm.o
gcc -m32 -c -fno-stack-protector -o out/kernelc.o kernel.c
ld -m elf_i386 -T linker.ld -o out/kernel.iso out/kernelasm.o out/kernelc.o