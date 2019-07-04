CC := g++
SRCDIR := src
BINDIR := bin
TESTDIR := test

SRC := $(SRCDIR)/*.cpp

CFLAGS := -g -Wall -O3 -std=c++14
INC := -I $(SRCDIR)/include/

main:
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(BINDIR)/main

all: main

run:
	$(BINDIR)/main

tests:
	@for i in $$(seq 1 2); do \
		$(BINDIR)/main < ./$(TESTDIR)/$$i.in > ./$(TESTDIR)/t$$i.out; \
		diff ./$(TESTDIR)/$$i.out ./$(TESTDIR)/t$$i.out; \
		rm ./$(TESTDIR)/t$$i.out; \
	done

clean:
	$(RM) -r $(BINDIR)/*
