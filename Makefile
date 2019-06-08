CC := g++
SRCDIR := src
OBJDIR := build
BINDIR := bin

SRC := src/*.cpp

CFLAGS := -g -Wall -O3 -std=c++14
INC := -I src/include/

VARIACOES := QC QPE QM3 QI1 QI5 QI10 QNR
TIPOS := Ale OrdC OrdD
TAMANHOS := 50 100 150 200 250 300 350 400 450 500
COMPLETION := 000


$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

main:
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(BINDIR)/main

all: main
	
clean:
	$(RM) -r $(OBJDIR)/* $(BINDIR)/*

test:
	@for tamanho in $(TAMANHOS) ; do \
		for tipo in $(TIPOS) ; do \
			for variacao in $(VARIACOES) ; do \
    		echo "./$(BINDIR)/main $$variacao $$tipo $$tamanho"$(COMPLETION) ; \
    		$(BINDIR)/main $$variacao $$tipo $$tamanho"$(COMPLETION)" ; \
	  	done \
	  done \
  done

ulimit:
	ulimit -s 512000
