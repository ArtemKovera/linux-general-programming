#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

#define PORT        5001
#define BUFF_LEN    512

char buf[BUFF_LEN];


int main()
{
    int mySocket, i, bytes, status;
    unsigned int size;
    struct sockaddr_in addr_server;
    struct sockaddr_in addr_from;

    struct hostent *hostinfo;

    hostinfo = gethostbyname("127.0.0.1");
    if(hostinfo == NULL)
    {
        fprintf(stderr, "Unknown address\n");
        exit(EXIT_FAILURE);
    }

    addr_server.sin_family = AF_INET;
    addr_server.sin_port   = htons(PORT);
    addr_server.sin_addr.s_addr = INADDR_ANY;

    mySocket = socket(PF_INET, SOCK_DGRAM, 0);
    if(mySocket < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    
    status = bind(mySocket, (struct sockaddr*)&addr_server, sizeof(addr_server));
    if(status < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    
    size = sizeof(addr_from);
    bytes = recvfrom(mySocket, buf, BUFF_LEN, 0, (struct sockaddr*) &addr_from, &size);

    strcat(buf, " (FROM SERVER)");

    bytes = sendto(mySocket, buf, strlen(buf) + 1, 0, (struct sockaddr*) &addr_from, sizeof(addr_from));
    if(bytes < 0)
    {
        perror("sendto");
        close(mySocket);
        exit(EXIT_FAILURE);
    }

    close(mySocket);
    
    return 0;
}