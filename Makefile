CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=gnu89
DEPS=hsh.h
OBJ=hsh.o path.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hsh: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
