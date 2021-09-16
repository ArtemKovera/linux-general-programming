#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include"robust_io.h"
#include"open_client_fd.h"

#define MAXLINE 1024


int main(int argc, char **argv)
{   
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int clientFD;
    char *host, *port, buf[MAXLINE];
    rioT rio;
    
    host = argv[1];
    port = argv[2];

    clientFD = openClientFD(host, port);
    rioReadInitb(&rio, clientFD);

    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        rioWriten(clientFD, buf, strlen(buf));
        rioReadLineb(&rio, buf, MAXLINE);
        fputs(buf, stdout);
    }
    
    if(close(clientFD))
    {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
