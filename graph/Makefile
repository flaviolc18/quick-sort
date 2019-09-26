CC := g++
SRCDIR := src
BINDIR := bin
TESTDIR := test

SRC := src/*.cpp

CFLAGS := -g -Wall -O3 -std=c++14 -ggdb3
INC := -I $(SRCDIR)/include/

main:
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(BINDIR)/main

all: main

check:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose $(BINDIR)/main ${FILE}

run:
	$(BINDIR)/main ${ARGS}

clean:
	$(RM) -r $(BINDIR)/*
