#ifndef __RWLOCK_H__
#define __RWLOCK_H__

#include <semaphore.h>
#include <stdlib.h>

struct RWLock_t {
	sem_t lock;
	sem_t writelock;
	int readers;
};
typedef struct RWLock_t RWLock;

RWLock *rwlock_new(void);
void rwlock_destroy(RWLock *rw);

void rwlock_acquire_readlock(RWLock *rw);
void rwlock_release_readlock(RWLock *rw);

void rwlock_acquire_writelock(RWLock *rw);
void rwlock_release_writelock(RWLock *rw);

#endif
