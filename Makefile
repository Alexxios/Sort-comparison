CC = clang++
CFLAGS = -std=c++17 -Wall

all: main

main: main.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.txt main