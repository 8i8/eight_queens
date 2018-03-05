EXE = queens
SRC = queens.c board.c trie.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -g
CFLAGS += -Wall -Wextra -pedantic
#CFLAG += -fsanitize=address -fno-omit-frame-pointer

.PHONY: all clean distclean

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(EXE)

$(OBJ): board.h trie.h Makefile

clean:
	rm -f *.o

distclean: clean
	rm -f queens a.out scratch.c
