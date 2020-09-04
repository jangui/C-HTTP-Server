all: server

LIBS := -pthread
CFLAGS := -Wall
CC := gcc

server: server.o
	$(CC) $(CFLAGS) server.o -o server $(LIBS)

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

clean:
	rm -f *.o server

