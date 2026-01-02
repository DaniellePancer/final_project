CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: test_scanf

test_scanf: my_scanf.c test_scanf.c
	$(CC) $(CFLAGS) my_scanf.c test_scanf.c -o test_scanf

run:
	./test_scanf

clean:
	rm -f test_scanf
