CC = gcc
C_FLAGS = -std=c11 -Wall -Wextra 

main:
	$(CC) $(C_FLAGS) main.c list.c -o main

debug:
	$(CC) $(C_FLAGS) -g main.c list.c -o main

clean:
	rm ./main
