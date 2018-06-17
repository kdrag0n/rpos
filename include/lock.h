#pragma once
#include "types.h"

struct lock {
    bool state;
    unsigned int usages;
    unsigned int last_cpu;
};

void lock_get(struct lock *lock);
void lock_release(struct lock *lock);
void lock_dump(char *lock_name, struct lock *lock);
struct lock *lock_create(void);

#define lock_init(var_name)     (var_name = lock_create())
