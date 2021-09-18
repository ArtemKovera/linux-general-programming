/*
    Function implementations for echo server
    The implementations are anologous to the ones from the book
    "Computer Systems: A Programmer's Perspective" by Randal Bryant and David O'Hallaron
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

void echo(int connFD)
{
    size_t n;
    char buf [MAXLINE];
    rioT rio;
    rioReadInitb(&rio, connFD);

    while((n = rioReadLineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("server received %d bytes\n", (int) n);
        rioWriten(connFD, buf, n);
    }
}

int openListenFD(char *port)
{
    struct addrinfo hints, *listp, *p;
    int listenFD, optval=1;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
   
    if(getaddrinfo(NULL, port, &hints, &listp))
    {
        fprintf(stderr, "getaddrinfo failure\n");
        exit(EXIT_FAILURE);
    }
    
    for (p = listp; p; p = p->ai_next)
    {
        if ((listenFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;
        
        if(setsockopt(listenFD, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        if (bind(listenFD, p->ai_addr, p->ai_addrlen) == 0)
            break;
        
        if(close(listenFD))
        {
            perror("close");
            exit(EXIT_FAILURE);
        }

    }

    freeaddrinfo(listp);

    if(!p)
        return -1;

    if (listen(listenFD, LISTENQ) < 0)
    {
        if(close(listenFD))
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
    }

    return listenFD;
}