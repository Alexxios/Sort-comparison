CC = g++
CFLAGS = -std=c++17 -Wall

all: main

main: sources/main.cpp
	$(CC) $(CFLAGS) $< -o $@

efficient: sources/efficient.cpp
	$(CC) $(CFLAGS) $< -o main

insert: sources/insert.cpp
	$(CC) $(CFLAGS) $< -o main

clean:
	rm -rf *.txt main