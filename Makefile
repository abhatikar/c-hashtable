# Usage:
# Run 'make test' to execute the test program.
# Run 'make valgrind' to run the test program in Valgrind.
# Run 'make clean' to remove compiled files.

CC			:= gcc
CFLAGS			:= -Wall -Wextra -std=c99 -g -D_XOPEN_SOURCE=500
SRC			:= hashmap.c main.c
DEPS			:= $(SRC) $(SRC:.c=.h)
TARGET			:= hashtable

.PHONY: test valgrind submit clean

default: compile

compile:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

test: compile
	./hashtable

valgrind:
	valgrind --tool=memcheck ./hashtable

clean:
	-rm -f *.o
	-rm -f $(TARGET) $(SRC:.c)
