#include "lock.h"
#include "log.h"
#include "utils.h"

void lock_get(struct lock *lock) {
    while (lock->state) {}

    lock->state = 1;
    lock->usages += 1;
    lock->last_cpu = cpuid();
}

void lock_release(struct lock *lock) {
    lock->state = 0;
}

void lock_dump(char *lock_name, struct lock *lock) {
    pr_debug("Lock: %s state=%d usages=%d last_cpu=%d", lock_name, lock->state, lock->usages, lock->last_cpu);
}

struct lock *lock_create(void) {
    static struct lock lock = {
        .state = 0,
        .usages = 0,
        .last_cpu = 0,
    };

    lock.last_cpu = cpuid();

    return &lock;
}
