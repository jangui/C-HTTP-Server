all: server

LIBS := -pthread
CFLAGS := -Wall
CC := gcc

debug: CFLAGS += -DDEBUG=1
debug: server

server: server.o signalHandling.o
	$(CC) $(CFLAGS) server.o signalHandling.o -o server $(LIBS)

server.o: server.c
	$(CC) $(cflags) -c server.c

signalHandling.o: signalHandling.c signalHandling.h
	$(CC) $(cflags) -c signalHandling.c

clean:
	rm -f *.o server

