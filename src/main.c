#include "uart.h"

void kernel_main(void) {
    uart_init();
    uart_send_string("Hello, world!\n");

    while (1) { // echo loop
        uart_send(uart_recv());
    }
}
