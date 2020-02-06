CC = g++
BIN = bin
SRC = src
C_FLAGS = -Wall -Wextra

EXECUTABLE = compiler

all: buildrepo $(BIN)/$(EXECUTABLE)

clean:
	rm $(BIN)/$(EXECUTABLE)

run: all

	./$(BIN)/$(EXECUTABLE)

buildrepo:
	mkdir -p bin src

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CC) $(C_FLAGS) $^ -o $@
