#include "mm.h"

.section ".text.boot"

// entry point for execution. all 4 cores execute this simultaneously.
.globl _start
_start:
    // b    cpu0_only       // only execute on cpu 0
    b       master_init     // begin kernel initialization

// rpi3 has 4 cores. each starts executing at the same entry point.
// we only want 1 for simplicity, so hang the rest.
.globl cpu0_only
cpu0_only:
    mrs     x0, mpidr_el1   // copy mpidr_el1 (cpu info) into x0
    and     x0, x0, #0xFF   // strip last 2 bytes - mpidr_el1 isn't ONLY cpu id
    b       proc_hang       // if (x0 != 0), hang the cpu

// fill the .bss elf section with zeroes
master_init:
    adr     x0, bss_begin   // copy address of bss_begin to x0
    adr     x1, bss_end     // copy address of bss_end to x1
    sub     x1, x1, x0      // x1 = x1 - x0
    bl      memzero         // branch, LR/return addr in x30

    mov     sp, #LOW_MEMORY // start stack at reserved low memory region
    bl      kernel_main     // start the kernel
    b       proc_hang       // just in case (this is BAD)

// an infinite loop to hang the cpu
proc_hang:
    b       proc_hang
