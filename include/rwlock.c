#include "rwlock.h"

RWLock *rwlock_new(void) {
	RWLock *self = malloc(sizeof(RWLock));
	self->readers = 0;
	sem_init(&self->lock, 0, 1);
	sem_init(&self->writelock, 0, 1);
	return self;
}

void rwlock_acquire_readlock(RWLock *rw) {
	sem_wait(&rw->lock);
	rw->readers++;
	if (rw->readers == 1)
		sem_wait(&rw->writelock);
	sem_post(&rw->lock);
}

void rwlock_release_readlock(RWLock *rw) {
	sem_wait(&rw->lock);
	rw->readers--;
	if (rw->readers == 0)
		sem_post(&rw->writelock);
	sem_post(&rw->lock);
}

void rwlock_acquire_writelock(RWLock *rw) {
	sem_wait(&rw->writelock);
}

void rwlock_release_writelock(RWLock *rw) {
	sem_post(&rw->writelock);
}

void rwlock_destroy(RWLock *rw) {
	sem_destroy(&rw->lock);
	sem_destroy(&rw->lock);
	free(rw);
}
