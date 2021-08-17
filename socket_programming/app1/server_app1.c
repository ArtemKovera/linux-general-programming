/*
    A simple server
    Adapted from https://www.youtube.com/watch?v=09_2hrqAXQ0&t 
*/
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define MAX_NUMBER_CLIENTS 5
#define BUFF_SIZE 256

int main()
{   
    int rflag;
    
    //socket IPv4/TCP
    int server = socket(AF_INET, SOCK_STREAM, 0);
    
    if(server == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons(34543);

    rflag = bind(server, (struct sockaddr *) &address, sizeof(address));
    if(rflag == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    rflag = listen(server, MAX_NUMBER_CLIENTS);
    if(rflag == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    } 
    
    socklen_t addressLength = sizeof(address);
    int fd = accept(server, (struct sockaddr * ) &address, &addressLength);
    if(fd == -1)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    ssize_t rbytes;
    ssize_t wbytes;
    char buffer[BUFF_SIZE];
    rbytes = read(fd, buffer, BUFF_SIZE);
    if(rbytes == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    if(rbytes == 0)
    {
        printf("End of file\n");
    }

    write(STDIN_FILENO, buffer, rbytes);
    wbytes = write(fd, buffer, rbytes);
    if(wbytes == -1)
    {
        perror("write to client error");
        exit(EXIT_FAILURE);
    }    

    return 0;
}

