TARGET = example
CC=gcc
CFLAGS =-I. -Wall -Wextra
HEADERS = queue.h
OBJ = example.o circular_queue.o

%.o : %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(TARGET) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm ./$(TARGET) *.o 