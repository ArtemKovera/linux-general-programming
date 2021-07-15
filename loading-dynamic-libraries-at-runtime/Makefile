CC=gcc
CFLAGS=-Wall 

all: prog libsecond.so libfirst.so

prog: main.c
	$(CC) $(CFLAGS) -o $@ main.c -ldl

libsecond.so: second-lib.c second-lib.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ second-lib.c -lc

libfirst.so: first-lib.c first-lib.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ first-lib.c -lc

clean:
	rm *.so prog