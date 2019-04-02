#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "rwlock.h"

RWLock rw;
int num = 0;


void *reader(void *arg) {
	int i;
	for (i = 0; i < 10; i++) {
		rwlock_acquire_readlock(&rw);
		printf("Reader %s: %d\n", (char *) arg, num);
		rwlock_release_writelock(&rw);
		sleep((int) rand() % 5);
	}
	return NULL;
}

void *writer(void *arg) {
	int i;
	for (i = 0; i < 10; i++) {
		rwlock_acquire_writelock(&rw);
		num = num + 1;
		printf("Writer %s: %d\n", (char *) arg, num);
		rwlock_release_writelock(&rw);
		sleep((int) rand() % 5);
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	rwlock_init(&rw);
	pthread_t p1, p2, p3;
	pthread_create(&p1, NULL, reader, "A");
	pthread_create(&p2, NULL, reader, "B");
	pthread_create(&p3, NULL, writer, "C");
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	pthread_join(p3, NULL);
	printf("%d\n", num);
	return 0;
}
