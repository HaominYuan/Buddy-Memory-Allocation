#include "sbuddy.h"
#include <stdio.h>

SBuddy *sbuddy_new(int size) {
	SBuddy *self = malloc(sizeof(SBuddy));
	self->buddy = buddy_new(size);
	self->rw = rwlock_new();
	return self;
}

void sbuddy_destroy(SBuddy *self) {
	buddy_destroy(&self->buddy);
	rwlock_destroy(self->rw);
	free(self);
}

int sbuddy_alloc(SBuddy *self, int size) {
	int offset = 0;
	rwlock_acquire_writelock(self->rw);
	offset = buddy_alloc(self->buddy, size);
	rwlock_release_writelock(self->rw);
	return offset;
}

void sbuddy_free(SBuddy *self, int offset) {
	rwlock_acquire_writelock(self->rw);
	buddy_free(self->buddy, offset);
	rwlock_release_writelock(self->rw);
}

int sbuddy_size(SBuddy *self, int offset) {
	int size;
	rwlock_acquire_readlock(self->rw);
	size = buddy_size(self->buddy, offset);
	rwlock_release_readlock(self->rw);
	return size;
}
