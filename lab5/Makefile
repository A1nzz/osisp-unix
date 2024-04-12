CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: multithreaded_sort

multithreaded_sort: multithreaded_sort.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f multithreaded_sort