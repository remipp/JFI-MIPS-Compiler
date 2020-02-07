CC = g++
BIN = bin
SRC = src
BUILD = build
C_FLAGS = -Wall -Wextra -std=c++17
LD = ld
SOURCE_FILES = $(shell find src -name '*.cpp' -exec basename {} \;)
OBJECT_FILES = $(SOURCE_FILES:%.cpp=$(BUILD)/%.o)

EXECUTABLE = compiler

all: buildrepo $(BIN)/$(EXECUTABLE)

clean:
	rm $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

buildrepo:
	mkdir -p bin src build

build/%.o: src/%.cpp
	$(CC) -c $(C_FLAGS) $^ -o $@

$(BIN)/$(EXECUTABLE): $(OBJECT_FILES)
	$(CC) $(LDFLAGS) $(C_FLAGS) $^ -o $@
