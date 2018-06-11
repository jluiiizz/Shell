SRC=src/main.c
BIN=bin/jshell

default: $(BIN)

$(BIN): $(SRC)
	gcc $? -o $(BIN)

clean:
	-rm -f $(BIN)
