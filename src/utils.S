// utility functions

// set the value of a 32-bit register from 64-bit register x0
.globl put32
put32:
    str     w1, [x0]    // write x0 into w1
    ret                 // return

// get the value of a 32-bit register, return in 64-bit register x0
.globl get32
get32:
    ldr     w0, [x0]    // copy w1 into x0
    ret                 // return

// sleep by idle looping for x0 cycles
.globl sleep
sleep:
    subs    x0, x0, #1  // subtract 1 from x0 , store flags (Z: cond)
    bne     sleep       // loop to self if not Z
    ret                 // return

// get the current cpu id
.globl cpuid
cpuid:
    mrs     x0, mpidr_el1   // copy mpidr_el1 (cpu info) into x0
    and     x0, x0, #0xFF   // strip last 2 bytes - mpidr_el1 isn't ONLY cpu id
    ret                     // cpu id in x0

// get the current cpu exception level
.globl get_el
get_el:
    mrs x0, CurrentEL       // get CurrentEL register into x0
    lsr x0, x0, #2          // logical shift right 2 bits: first 2 bits are reserved with value 0
    ret                     // return exception level
