#pragma once
#include "printf.h"

#define L_UNKNOWN   -1
#define L_DEBUG     0
#define L_INFO      1
#define L_WARN      2
#define L_ERROR     3
#define L_FATAL     4

extern unsigned int log_idx;

void _printk(unsigned int level, char* fmt, va_list va);
void printk(unsigned int level, char *fmt, ...);

#define pr_debug(fmt, ...)      printk(L_DEBUG, fmt, ##__VA_ARGS__)
#define pr_info(fmt, ...)       printk(L_INFO, fmt, ##__VA_ARGS__)
#define pr_warn(fmt, ...)       printk(L_WARN, fmt, ##__VA_ARGS__)
#define pr_error(fmt, ...)      printk(L_ERROR, fmt, ##__VA_ARGS__)
#define pr_fatal(fmt, ...)      printk(L_FATAL, fmt, ##__VA_ARGS__)
