#ifndef __SBUDDY_H__
#define __SBUDDY_H__

#include "buddy.h"
#include "rwlock.h"

#define T SBuddy_T
typedef struct T *T;

T sbuddy_new(int size);
void sbuddy_destroy(T *self);

int sbuddy_alloc(T self, int size);
void sbuddy_free(T self, int offset);

int sbuddy_size(T self, int offset);
#undef T
#endif
