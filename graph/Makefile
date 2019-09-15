CC := g++
SRCDIR := src
BINDIR := bin
TESTDIR := test

SRC := $(shell find $(SRCDIR) -type f -name *.cpp)

CFLAGS := -g -Wall -O3 -std=c++14
INC := -I $(SRCDIR)/include/

main:
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(BINDIR)/main

all: main

run:
	$(BINDIR)/main

clean:
	$(RM) -r $(BINDIR)/*
