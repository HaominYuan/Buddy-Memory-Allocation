#ifndef BUDDY_BUDDY_H
#define BUDDY_BUDDY_H

struct buddy;
struct buddy *buddy_new(int size);
void buddy_destory(struct buddy *self);

int buddy_alloc(struct buddy *self, int size);
void buddy_free(struct buddy *self, int offset);

int buddy_size(struct buddy *self, int offset);
#endif
