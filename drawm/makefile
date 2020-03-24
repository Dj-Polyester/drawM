IDIR =./include
ODIR =./obj
SRCDIR = ./src

CC=gcc
CFLAGS=-I$(IDIR) -I$(ODIR) 
LIBS = -lm
GTK = `pkg-config --cflags --libs gtk+-3.0` -export-dynamic 

_OBJ = canvas.o helpers.o signals.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
_INC = canvas.h global.h signals.h helpers.h 
INC = $(patsubst %,$(IDIR)/%,$(_INC))

all: clean main

main: $(OBJ)
	$(CC) $^ -o $@  $(CFLAGS) $(GTK) 
	
	
$(ODIR)/%.o: $(SRCDIR)/%.c 
	$(CC) -c $^ -o $@ $(CFLAGS) $(LIBS) $(GTK)

.PHONY: clean

clean:
	$(RM) $(ODIR)/*.o *~ core $(IDIR)/*~ 