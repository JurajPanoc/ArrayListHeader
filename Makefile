CC = gcc
C_FLAGS = -std=c11 -Wall -Wextra 

make_main:
	$(CC) $(C_FLAGS) main.c list.c -o main

clean:
	rm ./main
