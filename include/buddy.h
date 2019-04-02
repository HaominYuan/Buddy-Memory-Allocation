#ifndef __BUDDY_H__
#define __BUDDY_H__

#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Buddy_t {
	char size;
	char longest[1];
};
typedef struct Buddy_t Buddy;

Buddy *buddy_new(int size);
void buddy_destroy(Buddy *self);

int buddy_alloc(Buddy *self, int size);
void buddy_free(Buddy *self, int offset);

int buddy_size(Buddy *self, int offset);
#endif
