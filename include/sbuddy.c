#include "sbuddy.h"
#include <stdio.h>
#include <stdlib.h>

#define T SBuddy_T
struct SBuddy_T {
	Buddy_T  buddy;
	RWLock_T rw;
};

T sbuddy_new(int size) {
	T self = malloc(sizeof(*self));
	self->buddy = buddy_new(size);
	self->rw = rwlock_new();
	return self;
}

void sbuddy_destroy(T *self) {
	buddy_destroy(&(*self)->buddy);
	rwlock_destroy(&(*self)->rw);
	free(*self);
	*self = NULL;
}

int sbuddy_alloc(T self, int size) {
	int offset = 0;
	rwlock_acquire_writelock(self->rw);
	offset = buddy_alloc(self->buddy, size);
	rwlock_release_writelock(self->rw);
	return offset;
}

void sbuddy_free(T self, int offset) {
	rwlock_acquire_writelock(self->rw);
	buddy_free(self->buddy, offset);
	rwlock_release_writelock(self->rw);
}

int sbuddy_size(T self, int offset) {
	int size;
	rwlock_acquire_readlock(self->rw);
	size = buddy_size(self->buddy, offset);
	rwlock_release_readlock(self->rw);
	return size;
}
