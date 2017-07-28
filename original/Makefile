CC       = gcc
TARGET   = dictionary
CFLAGS   = -Wall -Werror -Wextra -pedantic -std=c99 -g
VALGRIND = valgrind --leak-check=full --show-reachable=yes
#SOURCES  = $(wildcard *.c)
SOURCES  = data.c dict_helpers.c helpers.c index.c
HEADERS  = $(wildcard *.h)
OBJECTS  = $(SOURCES:.c=.o)
A        = amd64
LIBS     = $(A)/list.o $(A)/main.o $(A)/dict.o $(A)/pair.o

.PHONY : valgrind indent clean

$(TARGET) :
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

valgrind : $(TARGET)
	$(VALGRIND) ./$(TARGET)

indent :
	mkdir _indent
	cp $(SOURCES) $(HEADERS) _indent/
	indent -kr -nut -brf -cli4 -l79 _indent/*

clean :
	rm -f $(TARGET) $(OBJECTS)
	rm -rf _indent/
	rm -f *.c~ *.h~
