HEADERS = src/*.h
SRC = src/*.c
CC = gcc
CFLAGS = -Wall -g
NAME = huffman

compile:
	@echo Compiling project
	@$(CC) $(SRC) $(HEADERS) $(CFLAGS) -o $(NAME)
	@echo Compilation successful