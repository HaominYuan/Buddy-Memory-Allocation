#ifndef __RWLOCK_H__
#define __RWLOCK_H__

#define T RWLock_T
typedef struct T *T;

T rwlock_new(void);
void rwlock_destroy(T *rw);

void rwlock_acquire_readlock(T rw);
void rwlock_release_readlock(T rw);

void rwlock_acquire_writelock(T rw);
void rwlock_release_writelock(T rw);
#undef T
#endif
