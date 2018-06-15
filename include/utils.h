#pragma once
#include "log.h"

extern void sleep(unsigned long);
extern void put32(unsigned long, unsigned int);
extern unsigned int get32(unsigned long);
extern unsigned int cpuid(void);

extern void cpu0_only(void);

char itoa(unsigned int num);
