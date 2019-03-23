#include <stdio.h>
#include <string.h>
#include "buddy.h"

int main(int argc, char *argv[]) {
	char cmd[80];
	int arg;
	struct buddy *b = buddy_new(32);
	puts("Enter q to quit");
	for (;;) {
		scanf("%s %d", cmd, &arg);
		printf("---%d\n", arg);
		if (strcmp(cmd, "alloc") == 0) {
			printf("allocted@%d\n", buddy_alloc(b, arg));
		} else if (strcmp(cmd, "free") == 0) {
			buddy_free(b, arg);
		} else if (strcmp(cmd, "size") == 0) {
			printf("size: %d\n", buddy_size(b, arg));
		} else if (strcmp(cmd, "q") == 0) {
			break;
		}
	}
	return 0;
}
