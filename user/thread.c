#include "kernel/types.h"
#include "kernel/stat.h"
// #include "kernel/defs.h"
#include "kernel/riscv.h"
// #include "kernel/spinlock.h"
#include "user/user.h"
#include "user/thread.h"

int thread_create(void *(start_routine)(void*), void *arg) 
{
    void* stack = malloc(PGSIZE);
    // Add PGSIZE to get the top of the stack instead of the bottom
    int clone_pid = clone(stack + PGSIZE);
    if (clone_pid < 0) {
        return -1;
    }
    else if (clone_pid == 0) {
        // this is a child
        start_routine(arg);
        exit(0);
    }
    else {
        // this is a parent. clone_pid is the pid of the child thread created
        return 0;
    }
    return -1;
}

void lock_init(lock_t* lock) 
{
    lock->locked = 0;
}

void lock_acquire(lock_t* lock)
{
    while(__sync_lock_test_and_set(&lock->locked, 1) != 0)
    {
        ;
    }
    __sync_synchronize();
}

void lock_release(lock_t* lock)
{  
    __sync_synchronize();
    __sync_lock_release(&lock->locked);
}

