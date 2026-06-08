riscv-none-elf-gcc -march=rv32imac_zicsr -c kernel.s -o kernel.o
riscv-none-elf-gcc -march=rv32imac_zicsr -ffreestanding -nostdlib -c kernel.c -o kernel_c.o
riscv-none-elf-gcc -march=rv32imac_zicsr -ffreestanding -nostdlib -c uart.c -o uart.o
riscv-none-elf-gcc -march=rv32imac_zicsr -ffreestanding -nostdlib -c mem.c -o mem.o
riscv-none-elf-gcc -march=rv32imac_zicsr -ffreestanding -nostdlib -c process.c -o process.o
riscv-none-elf-gcc -march=rv32imac_zicsr -ffreestanding -nostdlib -c scheduler.c -o scheduler.o
riscv-none-elf-gcc -march=rv32imac_zicsr -ffreestanding -nostdlib -c timer.c -o timer.o
riscv-none-elf-gcc -march=rv32imac_zicsr -c trap.s -o trap.o
riscv-none-elf-ld -T linker.ld kernel.o kernel_c.o uart.o mem.o process.o scheduler.o timer.o trap.o -o kernel.elf
qemu-system-riscv32 -machine virt -nographic -bios none -kernel kernel.elf