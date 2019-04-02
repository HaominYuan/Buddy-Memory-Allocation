INCS = ./include
CFLAGS = -Wall

main : main.c ./include/buddy.c
	gcc $^ -o $@ -I $(INCS) $(CFLAGS)

rwlock_test : rwlock_test.c ./include/rwlock.c
	gcc $^ -o $@ -I $(INCS) $(CFLAGS)

clean :
	rm -rf rwlock_test main
