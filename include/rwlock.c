#include "rwlock.h"

void rwlock_init(RWLock *rw) {
	rw->readers = 0;
	sem_init(&rw->lock, 0, 1);
	sem_init(&rw->writelock, 0, 1);
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
