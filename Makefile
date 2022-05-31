CFLAGS= -Wall -Wextra -ggdb -O3 -std=gnu11

projup: main.c
	cc main.c -o projup ${CFLAGS}

install: projup
	install -D projup /usr/bin/
	install -D projup.1 /usr/local/man/man1/

uninstall:
	rm /usr/bin/projup
	
clean:
	rm projup
