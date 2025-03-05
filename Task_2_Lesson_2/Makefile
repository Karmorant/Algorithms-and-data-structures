CXX = g++
CXXFLAGS = -std=c++11
TARGET = task_2
SRC = task_2.cpp
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