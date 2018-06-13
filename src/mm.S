// zero out a region of memory
.globl memzero
memzero:
    str     xzr, [x0], #8   // store 8 bytes of zeroes to x0
    subs    x1, x1, #8      // subtract 8 from x1
    b.gt    memzero         // repeat by self looping if not done
    ret                     // return
