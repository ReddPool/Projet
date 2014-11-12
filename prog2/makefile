SHELL = /bin/bash
CC    = gcc

FLAGS        = -std=gnu99
CFLAGS       = -Wall
DEBUGFLAGS   = -O0 -g
RELEASEFLAGS = -O2 -D NDEBUG

OPTRUNDBG = --length 9 -d 3 -k 6 -f tests/random2.fa

NAME = extract_motif

TARGET  = $(NAME)
TARGETC = extract_motif.c
PRESOURCES=$(wildcard *.c)
SOURCES := $(filter-out $(TARGETC),$(PRESOURCES))
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))
COMMON  =
HEADERS = $(wildcard *.h)

all: $(TARGET)


$(TARGET): $(TARGETC) $(OBJECTS)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) $(TARGETC) $(OBJECTS) -o $(TARGET)

release: $(SOURCES) $(HEADERS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(RELEASEFLAGS) -o $(TARGET) $(SOURCES)

$(OBJDIR)/%.o: $(LIBDIR)/%.c $(HEADERS) $(COMMON)
	$(CC) $(FLAGS) $(CFLAGS) $(DEBUGFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR)/*.o -f

mrproper: clean
	rm $(TARGET)

rundbg: all
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all  ./$(TARGET) $(OPTRUNDBG)

.PHONY: clean rundbg
