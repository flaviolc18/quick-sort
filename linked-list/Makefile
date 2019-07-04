CC := g++
SRCDIR := src
OBJDIR := build
BINDIR := bin

MAIN := program/main.cpp

CFLAGS := -g -Wall -O3 -std=c++14
INC := -I include/

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

main:
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(MAIN) -o $(BINDIR)/main

all: main

run:
	$(BINDIR)/main < $(FILE)
	
clean:
	$(RM) -r $(OBJDIR)/* $(BINDIR)/*
