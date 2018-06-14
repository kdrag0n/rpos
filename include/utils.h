#pragma once

extern void sleep(unsigned long);
extern void put32(unsigned long, unsigned int);
extern unsigned int get32(unsigned long);
extern unsigned int cpuid(void);

char itoa(unsigned int num);
