.POSIX:
CFLAGS = -O3 -Wall -Wextra -D_XOPEN_SOURCE=500
PREFIX = /usr/local
main: main.c
	$(CC) $(CFLAGS) src/* -Iinclude/ main.c -o blue

all: main

clean: 
	rm -f blue

install:
	cp blue $(DESTDIR)$(PREFIX)/bin/

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/blue

PHONY = all clean install uninstall
