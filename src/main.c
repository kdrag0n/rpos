#include "uart.h"
#include "utils.h"
#include "types.h"

bool uart_init_done = 0;
unsigned int hello_cpuid = 0;

void kernel_main(void) {
    if (cpuid() == 0) {
        uart_init();
        init_printf(0, uart_putc);
        pr_debug("Mini UART initialized on cpu%u", cpuid());
        uart_init_done = 1;
    } else {
        while (!uart_init_done) {
            sleep(150);
        }
    }

    while (hello_cpuid != cpuid()) {
        sleep(100);
    }

    pr_debug("Init on cpu%u", cpuid());
    hello_cpuid++;

    pr_debug("Hanging all except cpu0...");

    cpu0_only();
    pr_info("Starting UART echo on cpu0");

    char buf[256];
    int buf_pos = 0;

    while (1) { // echo loop
        char ch = uart_recv();
        buf[buf_pos++] = ch;
        buf[buf_pos] = '\0';

        if (ch == '\n') {
            uart_send('\n');
            uart_send_string(buf);
            uart_send('\n');

            buf_pos = 0;
        }
    }
}
