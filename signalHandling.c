#include <stdlib.h>         // exit
#include <errno.h>          // errno
#include <stdio.h>          // printf, perror
#include <unistd.h>         // close
#include <signal.h>         // sigaction, sigset_t, sigprocmask, sigemptyset

#ifndef DEBUG
  #define DEBUG 0
#endif

extern int socketfd;

void safeExit(int signum) {
  // if no connections exit
  /*
  if (NO CONNECTIONS) {
    close(socketfd);
    exit(0);
  }    
  */
  // else close all connections
  /* while ( clients still not disconnected) {
      ask threads to terminate
      sleep(1);
  */
  close(socketfd);
  if (DEBUG) {
    printf("server shutdown gracefully\n");
  }
  exit(0);
}

void setupSignalHandling() {
  errno = 0;
  struct sigaction newAction, oldAction;
  sigemptyset(&newAction.sa_mask);
  sigaddset(&newAction.sa_mask, SIGINT);
  newAction.sa_handler = safeExit;
  sigaction(SIGINT, &newAction, &oldAction);
  if (errno != 0) {
    perror("failed to set up signal handler");
    exit(errno);
  }
  if (DEBUG) {
    printf("signal handler setup\n");
  }
}
