CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: test_scanf manual_test

test_scanf: test_scanf.c
	$(CC) $(CFLAGS) test_scanf.c -o test_scanf

manual_test: manual_test.c
	$(CC) $(CFLAGS) manual_test.c -o manual_test

run:
	./test_scanf

run_manual:

	./manual_test

clean:
	rm -f test_scanf manual_test
