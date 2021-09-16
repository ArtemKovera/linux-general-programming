/*  
    A function for establishing a connection with a server. 
    It returns an open socket descriptor that is ready for
    input and output.

    This function is analogous to one example from the book "Computer Systems: A Programmer's Perspective"
    by Randal Bryant and David O'Hallaron    
*/
#include"open_client_fd.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

int openClientFD(const char* hostname, const char* port)
{
    int clientFD, status;
    struct addrinfo hints, *listp, *p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;

    if( (status = getaddrinfo(hostname, port, &hints, &listp)) != 0)
    {
        fprintf(stderr, "getaddrinfo error:%s\n", gai_strerror(status));
        exit(EXIT_FAILURE);        
    }
    
    for (p = listp; p; p = p->ai_next)
    {
        if ((clientFD = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
            continue;
        
        if (connect(clientFD, p->ai_addr, p->ai_addrlen) != -1)
            break;
        
        if(close(clientFD))
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
    }

    freeaddrinfo(listp);

    if(!p)
        return -1;
    else
        return clientFD;
    
}