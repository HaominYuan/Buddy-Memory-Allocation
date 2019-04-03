#include <stdio.h>
#include <string.h>
#include "sbuddy.h"

int main(int argc, char *argv[]) {
	SBuddy *buddy = sbuddy_new(32);
	printf("%d\n", sbuddy_alloc(buddy, 16));
	printf("%d\n", sbuddy_size(buddy, 0));
	sbuddy_destroy(buddy);
	return 0;
}
