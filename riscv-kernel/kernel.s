.section .rodata
msg:
    .asciz "HELLO FROM KERNEL\n"

.section .text
.global _start
.global print_string
.global print_char
.global print_int
.global print_hex
.global jump_to_process

_start:
    li sp, 0x80010000
    call kernel_main
hang:
    j hang

kernel_main:
    call c_kernel_main
    ret

print_char:
    li t0, 0x10000000
    sb a0, 0(t0)
    ret

print_string:
    addi sp, sp, -16
    sw ra, 12(sp)
    sw t1, 8(sp)
    mv t1, a0
loop:
    lb t2, 0(t1)
    beq t2, x0, done
    mv a0, t2
    call print_char
    addi t1, t1, 1
    j loop
done:
    lw ra, 12(sp)
    lw t1, 8(sp)
    addi sp, sp, 16
    ret

print_int:
    addi sp, sp, -16
    sw ra, 12(sp)
    beq a0, x0, print_zero
    li t1, 10
    addi t2, sp, 11
fill_loop:
    rem t3, a0, t1
    addi t3, t3, 48
    sb t3, 0(t2)
    div a0, a0, t1
    addi t2, t2, -1
    bnez a0, fill_loop
    addi t2, t2, 1
    addi t4, sp, 12
print_loop:
    beq t2, t4, print_done
    lb a0, 0(t2)
    call print_char
    addi t2, t2, 1
    j print_loop
print_done:
    j restore
print_zero:
    li a0, '0'
    call print_char
restore:
    lw ra, 12(sp)
    addi sp, sp, 16
    ret

print_hex:
    addi sp, sp, -16
    sw ra, 12(sp)
    mv t5, a0
    li a0, '0'
    call print_char
    li a0, 'x'
    call print_char
    mv a0, t5
    beq a0, x0, hex_print_zero
    li t1, 16
    addi t2, sp, 11
hex_fill_loop:
    remu t3, a0, t1
    li t4, 9
    bgt t3, t4, hex_is_alpha
    addi t3, t3, 48
    j hex_store
hex_is_alpha:
    addi t3, t3, 87
hex_store:
    sb t3, 0(t2)
    divu a0, a0, t1
    addi t2, t2, -1
    bnez a0, hex_fill_loop
    addi t2, t2, 1
    addi t4, sp, 12
hex_print_loop:
    beq t2, t4, hex_print_done
    lb a0, 0(t2)
    call print_char
    addi t2, t2, 1
    j hex_print_loop
hex_print_done:
    j hex_restore
hex_print_zero:
    li a0, '0'
    call print_char
hex_restore:
    lw ra, 12(sp)
    addi sp, sp, 16
    ret

jump_to_process:
    lw t0, 128(a0)
    csrw mepc, t0

    lw sp, 132(a0)

    csrr t1, mstatus
    li   t2, ~(3 << 11)
    and  t1, t1, t2
    li   t3, (3 << 11)
    or   t1, t1, t3
    csrw mstatus, t1

    mret