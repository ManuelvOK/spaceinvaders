CC		=gcc

SRCDIR 	=src
OBJDIR	=build
INCDIR	=inc

EXE		=spaceinvaders

SRC 	=$(wildcard src/*.c)
DEP		=$(SRC:%.c=%.d)
OBJ		=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
INC		=-I./$(INCDIR)/

CFLAGS	=-std=c99 ${INC} -Wall -Wextra -Wpedantic -Werror
LDFLAGS	=-lncurses

VPATH 	=$(SRCDIR)

.PHONY: all clean debug

all: $(OBJ) $(EXE)

debug: CFLAGS += -g
debug: $(EXE)

$(OBJ): | $(OBJDIR)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

-include $(DEP)

%.d: %.c
	$(CC) -MM ${INC} $*.c > $*.d
	sed -i -e 's|.*:|$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$*).o:|' $*.d

build/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	-rm $(EXE) $(OBJ) $(DEP)
	-rm -r $(OBJDIR)

$(OBJDIR):
	mkdir $@
