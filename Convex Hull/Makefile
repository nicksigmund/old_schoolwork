##################################################
##												##
##	Nicholas Sigmund Makefile					##
##												##
##	PROG= program name							##
##  CC= compiler								##
##	SRCEXT= extention of source files			##
##	INCDIR= extention of header files			##
##	INCDIR= header file directory				##
##  SRCDIR= source file directory				##
##	FLAG= compiler FLAGS 						##
##	LIB= library links							##
##												##
##################################################

PROG= hull
CC= gcc

INCEXT=h
SRCEXT=c

INCDIR=inc
SRCDIR=src
FLAG= 
LIB=-lm
RMOTHERS= set*.txt


#################### DO NOT CHANGE ####################
INC = $(wildcard $(INCDIR)/*.$(INCEXT))
SRC = $(wildcard $(SRCDIR)/*.$(SRCEXT))
	
OBJ=$(SRC:.c=.o)
OBJDIR=$(SRCDIR)/obj
O=$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(OBJ))

all: $(PROG)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi
	$(CC) -c -o $@ $< $(FLAGS)

$(PROG): $(O)
	$(CC) $(FLAG) -o $(PROG) $(O) $(LIB)
	
clean:
	rm -fr $(OBJDIR) $(PROG) $(RMOTHERS)
#################### DO NOT CHANGE ####################