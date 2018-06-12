HEADERS = shell.h utils.h input.h history.h mathmode.h twitch.h

default: build

main.o: main.c $(HEADERS)
	gcc -c -Wall -Werror main.c -o main.o

build: main.o
	gcc main.o -o jshell

complete_build: main.o
	gcc main.o -o jshell
	-rm -f main.o
	-rm -f vgcore.*

clean:
	-rm -f main.o
	-rm -f jshell
	-rm -f vgcore.*
