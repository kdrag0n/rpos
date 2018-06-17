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
        while (!uart_init_done) {}
    }

    while (hello_cpuid != cpuid()) {}

    pr_debug("Init on cpu%u, exception level %d", cpuid(), get_el());
    hello_cpuid++;

    while (hello_cpuid != 4) {}
    if (cpuid() == 0) {
        pr_warn("Hanging all except cpu0...");
    }
    if (cpuid() != 0) {
        while (1) {}
    }

    uart_debug();
    pr_info("Starting echo loop on cpu0");

    while (1) {
        char ch = uart_recv();
        uart_send(ch);
    }
}
