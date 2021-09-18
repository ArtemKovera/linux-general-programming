#ifndef SERVER_ROUTINES_H_
#define SERVER_ROUTINES_H_

#define MAXLINE 1024

#define LISTENQ 1024

void echo(int connFD);

int openListenFD(char *port);

#endif