# Author: Shiva Patel
# File: Makefile
# Last Modified: 4-4-2026
# Purpose: Compiles the game library program into an executable and has a clean function.
CC = g++
TARGET = game_library
CFLAGS = -c -Wall -Wextra -std=c++11
OBJS = main.o Library.o
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
Library.o: Library.cpp Library.h
	$(CC) $(CFLAGS) Library.cpp
clean:
	rm -f *.o *~ $(TARGET)
