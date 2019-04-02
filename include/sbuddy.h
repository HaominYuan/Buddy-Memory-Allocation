#ifndef __SBUDDY_H__
#define __SBUDDY_H__

#include "buddy.h"
#include "rwlock.h"

struct SBuddy_t {
	Buddy *buddy;
	RWLock *rw;
};
typedef struct SBuddy_t SBuddy;

SBuddy *sbuddy_new(int size);
void sbuddy_destory(SBuddy *self);

int sbuddy_alloc(SBuddy *self, int size);
void sbuddy_free(SBuddy *self, int offset);

int sbuddy_size(SBuddy *self, int offset);
#endif
