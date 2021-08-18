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

#define BUFF_SIZE 256
#define PORT 34543
#define IP "127.0.0.1"
#define MESSAGE "Hello, server\n"
#define MESSAGE_LEN 14

int main()
{
    int erflag;

    int client = socket(AF_INET, SOCK_STREAM, 0);
    if(client == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    erflag = connect(client, (struct sockaddr * ) &address, sizeof(address));
    if(erflag == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    erflag = inet_pton(AF_INET, IP, &address.sin_addr);
    if(erflag == 0)
    {
        printf("inet_pton failed: src does not contain a character string" 
        " representing a valid network address in the specified address family.\n");
        exit(EXIT_FAILURE);
    }
    if(erflag == -1)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }
    
    ssize_t wbytes;
    ssize_t rbytes;
    wbytes = write(client, MESSAGE, MESSAGE_LEN);
    if(wbytes == -1)
    {
        perror("write to server error");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFF_SIZE];    
    
    rbytes = read(client, buffer, BUFF_SIZE);
    if(rbytes == -1)
    {
        perror("read from server error");
        exit(EXIT_FAILURE);
    }
    if(rbytes == 0)
    {
        printf("EOF occured\n");
    }

    write(STDOUT_FILENO, buffer, rbytes);
    
    sleep(10);

    close(client);

    return 0;
}