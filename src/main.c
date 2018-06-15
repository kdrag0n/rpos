#include "uart.h"
#include "utils.h"
#include "types.h"

bool uart_init_done;
unsigned int hello_cpuid;

void kernel_main(void) {
    if (cpuid() == 0) {
        uart_init();
        uart_send_string("Mini UART init completed on processor ");
        uart_send(itoa(cpuid()));
        uart_send('\n');
        uart_init_done = 1;
    } else {
        while (!uart_init_done) {
            sleep(150);
        }
    }

    while (hello_cpuid != cpuid()) {
        sleep(100);
    }

    uart_send_string("Hello from processor ");
    uart_send(itoa(cpuid()));
    uart_send_string("!\n");
    hello_cpuid++;

    uart_send_string("Processor messages completed, hanging all other than cpu0...");

    cpu0_only();
    uart_send_String("Welcome to cpu0!");

    char buf[256];
    int buf_pos;

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
