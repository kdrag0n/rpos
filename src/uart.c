#include "uart.h"
#include "peripherals/gpio.h"
#include "peripherals/uart.h"
#include "utils.h"
#include "types.h"
#include "lock.h"

static struct lock *uart_lock;
static struct lock *uart_str_lock;

void uart_init(void) {
    lock_init(uart_lock);
    lock_init(uart_str_lock);

    unsigned int selector;

    // the GPFSEL1 register controls alts for pins 10-19
    selector = get32(GPFSEL1);  // fetch gpio selections
    selector &= ~(7<<12);       // clear pin 14
    selector |= 2<<12;          // set alt 5 for pin 14 (UART TX)
    
    selector &= ~(7<<15);       // clear pin 15
    selector |= 2<<15;          // set alt 5 for pin 15 (UART RX)
    
    put32(GPFSEL1, selector);   // set gpio selections

    put32(GPPUD, 0);            // disable pull-up and pull-down
    sleep(150);
    put32(GPPUDCLK0, (1<<14) | (1<<15)); // do so for pins 14, 15
    sleep(150);
    put32(GPPUDCLK0, 0);        // remove control signal

    put32(AUX_ENABLES, 1);      // enable uart + register control
    put32(AUX_MU_CNTL_REG, 0);  // disable auto flow control, disable tx and rx
    put32(AUX_MU_IER_REG, 0);   // disable tx and rx irqs
    put32(AUX_MU_LCR_REG, 3);   // enable 8 bit mode
    put32(AUX_MU_MCR_REG, 0);   // set RTS line to be always high (3.3V)
    put32(AUX_MU_BAUD_REG, 270);// set baud rate to 115200
    // put32(AUX_MU_IIR_REG, 6);// clear fifo buffer

    put32(AUX_MU_CNTL_REG, 3);  // enable tx and rx
}

void uart_send(char c) {
    lock_get(uart_lock);

    while (1) {
        if (get32(AUX_MU_LSR_REG) & 0x20) {
            break;
        }
    }

    put32(AUX_MU_IO_REG, c);
    lock_release(uart_lock);
}

char uart_recv(void) {
    lock_get(uart_lock);

    while (1) {
        if (get32(AUX_MU_LSR_REG) & 0x01) {
            break;
        }
    }

    char val = get32(AUX_MU_IO_REG) & 0xFF;
    lock_release(uart_lock);
    return val;
}

void uart_send_string(char* str) {
    lock_get(uart_str_lock);

    for (int i = 0; str[i] != '\0'; i++) {
        uart_send((char) str[i]);
    }

    lock_release(uart_str_lock);
}

void uart_putc(void* p, char c) {
    uart_send(c);
}

void uart_debug(void) {
    lock_dump("uart_lock", uart_lock);
    lock_dump("uart_str_lock", uart_str_lock);
}
