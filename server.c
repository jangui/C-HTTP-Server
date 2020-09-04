#include <stdio.h>        // printf, perror
#include <unistd.h>       // close
#include <stdlib.h>       // exit
#include <errno.h>        // errno
#include <string.h>       // memset
#include <netinet/in.h>   // servaddr, INADDR_ANY, htons, htonl
#include <sys/socket.h>   // socket, bind, listen, accpet, AF_INET
                          // SOCK_STREAM, send

#define LISTENQ 10        // max size for connection queue
#define DEBUG 1           // debug flag

// debug macro
#define DBGMSG(msg) if (DEBUG) { printf(msg "\n"); }

int setupServer(int port)  {
  // create socket
  int socketfd;
  if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("error creating socket");
    exit(errno);
  }
  DBGMSG("socket succesfully created");

  // setup sockaddr_in
  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(port);

  // bind
    if (bind(socketfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
    perror("error binding to socket");
    exit(errno);
  }
  DBGMSG("socket succesfully bound");

  // listen
  if (listen(socketfd, LISTENQ) < 0) {
    perror("error listening on socket");
    exit(errno);
  }
  DBGMSG("listening on socket..");
  //int socketfd = setupServer(serverAddr, port);
  return socketfd;
}

void processConnection(int connfd) {
  DBGMSG("connection accepted");

  char *msg = "Hello World\n";
  if (send(connfd, msg, strlen(msg), 0) < 0) {
    perror("send failed");
    exit(errno);
  }
  if (close(connfd) < 0) {
    perror("error closing connection");
    exit(errno);
  }
  DBGMSG("connection closed");
}

int main(int argc, char *argv[]) {
  int port = 8080;
  int socketfd = setupServer(port);

  // wait for connections and process
  int connfd;
  while ((connfd = accept(socketfd, NULL, NULL))) {
    processConnection(connfd);
  }
  return 0;
}
