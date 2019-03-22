#include <stdio.h>
#include <string.h>
#include "buddy.h"

int main(int argc, char *argv[]) {
	char cmd[80] = "alloc";
	int arg = 8;
	struct buddy *b = buddy_new(32);
	while (1) {
		if (strcmp(cmd, "alloc") == 0) {
			printf("allocted@%d\n", buddy_alloc(b, arg));
		} else if (strcmp(cmd, "free") == 0) {
			buddy_free(b, arg);
		} else if (strcmp(cmd, "size") == 0) {
			printf("size: %d\n", buddy_size(b, arg));
		}
		break;
	}
	return 0;
}
