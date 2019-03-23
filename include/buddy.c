#include "buddy.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct buddy {
	char size;
	char longest[1];
};

#define LEFT_LEAF(index) ((index) * 2 + 1)
#define RIGHT_LEAF(index) ((index) * 2 + 2)
#define PARENT(index) (((index) - 1) / 2)

#define IS_POWER_OF_2(x) (!((x) & ((x) - 1)))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

unsigned fix_size(unsigned size) {
	size |= size >> 1;
	size |= size >> 2;
	size |= size >> 4;
	size |= size >> 8;
	size |= size >> 16;
	return size + 1;
}

static char convert(int size) {
	if (size <= 0)
		return -1;
	int left = 0, right = 31, mid = 0;
	while (left < right) {
		mid = left + (right - left) / 2;
		if ((1 << mid) < size) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}
	return (char) left;
}

struct buddy *buddy_new(int size) {
	struct buddy *self;
	int node_size, i;
	
	if (size < 1 || !IS_POWER_OF_2(size)) {
		return NULL;
	}

	self = (struct buddy *) malloc(2 * size * sizeof(char));

	self->size = convert(size);
	node_size = self->size + 1;

	for (i = 0; i < 2 * size - 1; i++) {
		if (IS_POWER_OF_2(i + 1))
			node_size = node_size - 1;
		self->longest[i] = (char) node_size;
	}

	return self;
}

void buddy_destory(struct buddy *self) {
	free(self);
}


int buddy_alloc(struct buddy *self, int size) {
	unsigned index = 0, offset = 0;
	char node_size;
	int lg_size;

	if (self == NULL || size < 1) {
		return -1;
	}

	if (!IS_POWER_OF_2(size)) {
		size = fix_size((unsigned int) size);
	}

	lg_size = convert(size);

	if (self->longest[index] < lg_size)
		return -1;

	for (node_size = self->size; node_size != lg_size; node_size -= 1) {
		if (self->longest[LEFT_LEAF(index)] >= lg_size) {
			index = LEFT_LEAF(index);
		} else {
			index = RIGHT_LEAF(index);
		}
	}

	self->longest[index] = -1;
	offset = (index + 1) * (1 << node_size) - (1 << self->size);

	while (index != 0) {
		index = PARENT(index);
		self->longest[index] = MAX(self->longest[LEFT_LEAF(index)], self->longest[RIGHT_LEAF(index)]);
	}
		return offset;
}

void buddy_free(struct buddy *self, int offset) {
	int node_size, index;
	char left_longest, right_longest;

	assert(self && offset >= 0 && offset < self->size);

	node_size = 0;
	index = (1 << self->size) - 1 + offset;

	for (; self->longest[index] != -1; index = PARENT(index)) {
		node_size = node_size + 1;
		if (index == 0)
			return;
	}

	self->longest[index] = (char) node_size;

	while (index) {
		index = PARENT(index);
		node_size = node_size + 1;

		left_longest = self->longest[LEFT_LEAF(index)];
		right_longest = self->longest[RIGHT_LEAF(index)];

		if (left_longest == right_longest && node_size - left_longest == 1) {
			self->longest[index] = (char) node_size;
		} else {
			self->longest[index] = MAX(left_longest, right_longest);
		}
	}
}

int buddy_size(struct buddy *self, int offset) {
	unsigned node_size, index = 0;
	assert(self && offset >= 0 && offset < self->size);

	node_size = 1;
	for (index = (1 << self->size) - 1; self->longest[index] != -1; index = PARENT(index)) {
		node_size = node_size + 1;
	}
	return 1 << node_size;
}
