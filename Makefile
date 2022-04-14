projup: main.c
	cc main.c -o projup -O3 -ggdb -std=gnu11

install: projup
	install projup /usr/bin/projup
clean:
	rm projup
