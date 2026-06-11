# riscv-from-scratch

This project contains a complete computing stack built from scratch — a two-pass RISC-V
assembler that converts assembly to binary with a ~100% accuracy; a RISC-V simulator that executes those binaries
with full signed/unsigned arithmetic, memory, and branch semantics — with a ~100% accuracy; a bare-metal RISC-V kernel that boots on QEMU, drives UART via memory-mapped I/O,
manages heap memory with a page-based free list, runs multiple processes, and switches
between them preemptively using timer interrupts and a trap handler that saves and restores
all 32 registers; and a C compiler with a hand-written lexer, recursive-descent parser that
produces an AST, and a code generator targeting RISC-V assembly — supporting integers,
variables, binary arithmetic, if/else, while loops, and return statements. Every layer feeds
the next: C source → compiler → assembly → assembler → binary → simulator or kernel on QEMU.
The above statistics mentioned about the Assembler and Simulator were based on autograding infrastructure by respective IIITD Officials.

updating readme soon !
(the project isn't completed yet)
thanks for visiting :)

