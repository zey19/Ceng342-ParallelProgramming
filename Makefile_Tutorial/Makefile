CC=gcc
CFLAGS=-I.
DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

18050111034: 18050111034.o hellofunc.o 
	$(CC) -o 18050111034 18050111034.o hellofunc.o
