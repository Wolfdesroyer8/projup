projup: main.c
	clang main.c -o projup -O3 -g -std=gnu11

install: projup
	install projup /usr/bin/projup
