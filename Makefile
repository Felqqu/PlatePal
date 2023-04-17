CC = gcc
CFLAGS = -Wall -Wextra -std=c18

default: PlatePal

PlatePal: PlatePal.o Recipes.o
	$(CC) $(CFLAGS) -o PlatePal PlatePal.o Recipes.o -lm

PlatePal.o: PlatePal.c Recipes.h
	$(CC) $(CFLAGS) -c PlatePal.c

Recipes.o: Recipes.c Recipes.h
	$(CC) $(CFLAGS) -c Recipes.c

clean:
	$(RM) PlatePal *.o *~