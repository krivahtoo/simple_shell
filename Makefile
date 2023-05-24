CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=gnu89 -ggdb
DEPS=hsh.h
OBJ=hsh.o path.o utils.o strings.o prompt.o builtin.o readline.o execute.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hsh: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
