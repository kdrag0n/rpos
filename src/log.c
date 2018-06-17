#include "log.h"
#include "printf.h"
#include "uart.h"

unsigned int log_seq = 0;

char loglevel_char(unsigned int level) {
    switch (level) {
        case L_DEBUG: return 'D';
        case L_INFO: return 'I';
        case L_WARN: return 'W';
        case L_ERROR: return 'E';
        case L_FATAL: return 'F';
        default: return '?';
    }
}

void _printk(unsigned int level, char *fmt, va_list va) {
    char fmt_full[518];
    tfp_sprintf(fmt_full, "%03u%c %s\r\n", log_seq++, loglevel_char(level), fmt);

    tfp_format(0, uart_putc, fmt_full, va);
}

void printk(unsigned int level, char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    _printk(level, fmt, va);
    va_end(va);
}
