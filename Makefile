HEADERS = shell.h utils.h input.h history.h mathmode.h twitch.h

default: build

program.o: main.c $(HEADERS)
	gcc -c main.c -o main.o

build: main.o
	gcc main.o -o jshell

clean:
	-rm -f main.o
	-rm -f jshell
	-rm -f vgcore.*
