#include <stdio.h>
#include <string.h>
#include "sbuddy.h"

int main(int argc, char *argv[]) {
	char cmd[80];
	int arg;
	SBuddy *buddy = sbuddy_new(32);
	Buddy *b = buddy->buddy;
	printf("%d\n", sbuddy_size(buddy, 0));
	sbuddy_destroy(buddy);
	return 0;
}
