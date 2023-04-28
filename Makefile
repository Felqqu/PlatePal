CC = gcc
CFLAGS = -Wall -Wextra -std=c18 

default: Main

Main: Main.o Platepal.o
	$(CC) $(CFLAGS) -o Main Main.o Platepal.o -lm -lmysqlclient

Main.o: Main.c Platepal.h
	$(CC) $(CFLAGS) -c Main.c

Platepal.o: Platepal.c Platepal.h
	$(CC) $(CFLAGS) -c Platepal.c

clean:
	$(RM) Main *.o *~