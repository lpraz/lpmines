CC = gcc

lpmines: src/main.c src/intops.c
	$(CC) -o bin/lpmines src/main.c src/intops.c
