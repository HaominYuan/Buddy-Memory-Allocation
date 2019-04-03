#include <semaphore.h>
#include <stdlib.h>
#include "rwlock.h"

#define T RWLock_T
struct T {
	sem_t lock;
	sem_t writelock;
	int readers;
};


T rwlock_new(void) {
	T self = malloc(sizeof(*self));
	self->readers = 0;
	sem_init(&self->lock, 0, 1);
	sem_init(&self->writelock, 0, 1);
	return self;
}

void rwlock_acquire_readlock(T rw) {
	sem_wait(&rw->lock);
	rw->readers++;
	if (rw->readers == 1)
		sem_wait(&rw->writelock);
	sem_post(&rw->lock);
}

void rwlock_release_readlock(T rw) {
	sem_wait(&rw->lock);
	rw->readers--;
	if (rw->readers == 0)
		sem_post(&rw->writelock);
	sem_post(&rw->lock);
}

void rwlock_acquire_writelock(T rw) {
	sem_wait(&rw->writelock);
}

void rwlock_release_writelock(T rw) {
	sem_post(&rw->writelock);
}

void rwlock_destroy(T *rw) {
	sem_destroy(&(*rw)->lock);
	sem_destroy(&(*rw)->lock);
	free(*rw);
	*rw = NULL;
}
