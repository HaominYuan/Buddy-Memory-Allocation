#ifndef __BUDDY_H__
#define __BUDDY_H__

#define T Buddy_T
typedef struct T *T;

T buddy_new(int size);
void buddy_destroy(T *self);
int buddy_alloc(T self, int size);
void buddy_free(T self, int offset);
int buddy_size(T self, int offset);
#undef T
#endif
