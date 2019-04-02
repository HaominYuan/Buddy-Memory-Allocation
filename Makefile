INCS = ./include
CFLAGS = -Wall

main : main.c ./include/*.c
	gcc $^ -o $@ -I $(INCS) $(CFLAGS)
	
clean :
	rm -rf main
