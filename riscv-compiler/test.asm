    addi x10, x0, 10
    sw x10, -4(sp)
    addi x10, x0, 5
    sw x10, -8(sp)
    lw x10, -4(sp)
    addi sp, sp, -4
    sw x10, 0(sp)
    lw x10, -8(sp)
    lw x11, 0(sp)
    addi sp, sp, 4
    add x10, x11, x10
    sw x10, -12(sp)
    lw x10, -12(sp)
    addi sp, sp, -4
    sw x10, 0(sp)
    addi x10, x0, 10
    lw x11, 0(sp)
    addi sp, sp, 4
    slt x10, x10, x11
    beq x10, x0, else_0
    lw x10, -12(sp)
    addi sp, sp, -4
    sw x10, 0(sp)
    addi x10, x0, 3
    lw x11, 0(sp)
    addi sp, sp, 4
    sub x10, x11, x10
    sw x10, -12(sp)
    jal x0, end_1
else_0:
    lw x10, -12(sp)
    addi sp, sp, -4
    sw x10, 0(sp)
    addi x10, x0, 1
    lw x11, 0(sp)
    addi sp, sp, 4
    add x10, x11, x10
    sw x10, -12(sp)
end_1:
loop_2:
    lw x10, -4(sp)
    addi sp, sp, -4
    sw x10, 0(sp)
    addi x10, x0, 0
    lw x11, 0(sp)
    addi sp, sp, 4
    slt x10, x10, x11
    beq x10, x0, end_3
    lw x10, -4(sp)
    addi sp, sp, -4
    sw x10, 0(sp)
    addi x10, x0, 1
    lw x11, 0(sp)
    addi sp, sp, 4
    sub x10, x11, x10
    sw x10, -4(sp)
    jal x0, loop_2
end_3:
    lw x10, -12(sp)
    jalr x0, 0(x1)

