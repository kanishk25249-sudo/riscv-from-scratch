#!/bin/bash
cd /c/Users/kanis/OneDrive/Desktop/risc-v-project/compiler
./compiler > prog.asm

head -n -3 prog.asm > prog_tmp.asm

cat >> prog_tmp.asm << 'EOF'
    lw t0, -12(sp)
    addi t1, x0, 10
    div t2, t0, t1
    mul t3, t2, t1
    sub t4, t0, t3
    addi t2, t2, 48
    addi t4, t4, 48
    lui t5, 0x10000
    sb t2, 0(t5)
    sb t4, 0(t5)
    lw x10, -12(sp)
halt_4:
    jal x0, halt_4
EOF

mv prog_tmp.asm prog.asm
echo "prog.asm generated with UART output"