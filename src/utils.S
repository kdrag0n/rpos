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
