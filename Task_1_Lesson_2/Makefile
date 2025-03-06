CXX = gcc
CXXFLAGS = -std=c99
TARGET = task_1
SRC = task_1.c
DATA_FILE = sorting_times.txt
PY_SCRIPT = py_graph.py

all: build run plot

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

plot:
	python3 $(PY_SCRIPT)

clean:
	rm -f $(TARGET) $(DATA_FILE)

.PHONY: all build run plot clean