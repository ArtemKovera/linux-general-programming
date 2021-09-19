/*
    An echo server.
    The code is analogous to one example from the book "Computer Systems: A Programmer's Perspective"
    by Randal Bryant and David O'Hallaron
*/
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include"robust_io.h"
#include"server_routines.h"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int listenFD, connFD;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char clientHostname[MAXLINE];
    char clientPort[MAXLINE];
    
    listenFD = openListenFD(argv[1]);

    while(1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        connFD = accept(listenFD, (struct sockaddr*)&clientaddr, &clientlen);
        if(connFD == -1)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        if(getnameinfo((struct sockaddr *) &clientaddr, clientlen, clientHostname, MAXLINE, clientPort, MAXLINE, 0))
        {
           perror("getnameinfo");
           exit(EXIT_FAILURE);
        }
        
        printf("Connected to (%s, %s)\n", clientHostname, clientPort);
        
        echo(connFD);

        if(close(connFD))
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        
    }

    return 0;
}