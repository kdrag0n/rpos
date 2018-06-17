#include "mm.h"
#include "arm/sysregs.h"

.section ".text.boot"

// entry point for execution. all 4 cores execute this simultaneously.
.globl _start
_start:
    b       master_init     // begin initialization

master_init:
    ldr     x0, =SCTLR_VALUE// set System Control Register
    ldr     x1, =SCTLR_MMU_DISABLED // load MMU disable flag
    orr     x0, x0, x1      // disable MMU
    msr     sctlr_el1, x0

    ldr     x0, =HCR_VALUE  // set Hypervisor Config Register
    msr     hcr_el2, x0

    ldr     x0, =SCR_VALUE  // set Secure Config Register
    msr     scr_el3, x0

    ldr     x0, =SPSR_VALUE // set Saved Program Status Register
    msr     spsr_el3, x0

    adr     x0, el1_kinit   // set Exception Link Register to el1_kinit
    msr     elr_el3, x0

    eret                    // return to elr

// fill the .bss elf section with zeroes, then start the kernel (C)
el1_kinit:
    adr     x0, bss_begin   // copy address of bss_begin to x0
    adr     x1, bss_end     // copy address of bss_end to x1
    sub     x1, x1, x0      // x1 = x1 - x0
    bl      memzero         // branch, LR/return addr in x30

    mov     sp, #LOW_MEMORY // start stack at reserved low memory region
    bl      kernel_main     // start the C kernel
    b       proc_hang       // just in case

// an infinite loop to hang the cpu
proc_hang:
    b       proc_hang       // loop
