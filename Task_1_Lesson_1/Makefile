CC = gcc
CFLAGS = -Wall -Wextra -I -fsanitize=address.
TEST_TARGET = test_canonicalize_path

all: $(TEST_TARGET)

$(TEST_TARGET): test_canonicalize_path.o canonicalize_path.o
	$(CC) $(CFLAGS) -o $(TEST_TARGET) test_canonicalize_path.o canonicalize_path.o

canonicalize_path.o: canonicalize_path.c canonicalize_path.h
	$(CC) $(CFLAGS) -c canonicalize_path.c

test_canonicalize_path.o: test_canonicalize_path.c canonicalize_path.h
	$(CC) $(CFLAGS) -c test_canonicalize_path.c

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f *.o $(TEST_TARGET)