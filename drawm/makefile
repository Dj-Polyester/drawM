INCDIR =./include
OBJDIR =./obj
SRCDIR = ./src

CC=gcc -g
CFLAGS=-I$(INCDIR) -I$(OBJDIR) 
LIBS = -lm
GTK = `pkg-config --cflags --libs gtk+-3.0` -export-dynamic 
GTK2 = `pkg-config --cflags --libs gtk+-2.0` -export-dynamic 
LIBPORTAL = -lportal


_OBJ = app.o helpers.o signals.o main.o 
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))
_INC = app.h global.h signals.h helpers.h 
INC = $(patsubst %,$(INCDIR)/%,$(_INC))

all: clean main

main: $(OBJ)
	$(CC) $^ -o $@  $(CFLAGS) $(GTK) $(LIBPORTAL) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CC) -c $^ -o $@ $(CFLAGS) $(GTK) $(GTK2)

.PHONY: clean

clean:
	$(RM) $(OBJDIR)/*.o *~ core $(INCDIR)/*~  