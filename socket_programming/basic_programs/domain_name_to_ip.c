/*
    Domain name to IP address translation with getnameinfo() and getaddrinfo() functions

    This program is analogous to one example from the book "Computer Systems: A Programmer's Perspective"
    by Randal Bryant and David O'Hallaron
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<string.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM;

    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0)
    {
        fprintf(stderr, "getaddrinfo error:%s\n", gai_strerror(rc));
        exit(EXIT_FAILURE);
    }
    
    
    flags = NI_NUMERICHOST;
    for (p = listp; p; p = p->ai_next)
    {
        if( (getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags)) != 0)
        {
            fprintf(stderr, "getnameinfo error\n");
            exit(EXIT_FAILURE);
        }
        printf("%s\n", buf);
    }

    freeaddrinfo(listp);

    return 0;
}