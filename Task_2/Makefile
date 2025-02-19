CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address
TARGET = browser_history

all: $(TARGET)

$(TARGET): test_browser_history.o browser_history.o
	$(CC) $(CFLAGS) -o $(TARGET) test_browser_history.o browser_history.o

browser_history.o: browser_history.c browser_history.h
	$(CC) $(CFLAGS) -c browser_history.c

test_browser_history.o: test_browser_history.c browser_history.h
	$(CC) $(CFLAGS) -c test_browser_history.c

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)