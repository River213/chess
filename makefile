CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror


default: game

game:  main.o szachy.o menu.o 
	$(CC) $(CFLAGS) -o game main.o szachy.o menu.o


main.o:  main.c 
	$(CC) $(CFLAGS) -c main.c


szachy.o:  szachy.c szachy.h 
	$(CC) $(CFLAGS) -c szachy.c


scanner.o:  menu.c menu.h 
	$(CC) $(CFLAGS) -c menu.c


clean: 
	$(RM) game *.o *~


