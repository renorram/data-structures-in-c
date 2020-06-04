TARGET = main
CC=gcc
CFLAGS =-I. -Wall -Wextra -Werror
HEADERS = tree.h
OBJ = main.o tree.o

.PHONY: clean

%.o : %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm ./$(TARGET) *.o