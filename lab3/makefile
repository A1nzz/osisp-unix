CC = gcc
CFLAGS = -Wall

all: invert_filter

invert_filter: main.o reverse.o
	$(CC) $(CFLAGS) -o invert_filter main.o reverse.o

main.o: main.c reverse.h
	$(CC) $(CFLAGS) -c main.c

reverse.o: reverse.c reverse.h
	$(CC) $(CFLAGS) -c reverse.c

.PHONY: clean
clean:
	rm -f invert_filter *.o

.PHONY: test
test: invert_filter
	@echo "Running tests..."
	@./invert_filter test_input.txt > test_output.txt
	@diff -u test_output.txt expected_output.txt
	@echo "Tests completed successfully"