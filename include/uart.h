#pragma once

void uart_init(void);
char uart_recv(void);
void uart_send(char c);
void uart_send_string(char* str);
void uart_putc(void* p, char c);
void uart_debug(void);
