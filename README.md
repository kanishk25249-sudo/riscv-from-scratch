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

just as an example :
below is a proof of 2 pipelines integrating :

initial set of instructions given to compiler

<img width="1052" height="551" alt="image" src="https://github.com/user-attachments/assets/914bd47b-1d35-4d31-9135-2c291f8fa489" />

compiler->assembler->kernel

<img width="1240" height="698" alt="image" src="https://github.com/user-attachments/assets/6b8cd500-f149-4835-b7be-438e7e906a75" />

compiler->assembler->simulator

<img width="1240" height="698" alt="image" src="https://github.com/user-attachments/assets/ba511dea-a711-4845-9e80-d3061eb23271" />

thanks for visiting :)

