/*
    This program demonstrates single machine IPC by using unix sockets
    This code is analogous to one example from the course
    Системное программирование by Технострим Mail.Ru Group
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

#define MAX_MSG_SIZE 1024 * 1024

void worker(int sock)
{
    char buffer[MAX_MSG_SIZE];
    ssize_t bytesRead;

    while (bytesRead = read(sock, buffer, MAX_MSG_SIZE))
    {
        if(bytesRead == -1)
        {
            if(errno == EINTR)
                continue;
            
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Client recieved %ld bytes\n", bytesRead);
    }
}

int main(int argc, char **argv)
{   

    if(argc != 2)
    {
        printf("Usage :%s <soket_type>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int socketType = strcmp(argv[1], "stream") == 0 ? SOCK_STREAM : SOCK_DGRAM;

    int sockets[2];

    int status = socketpair(AF_UNIX, socketType, 0, sockets);
    if(status == -1)
    {
        perror("socketpair");
        exit(EXIT_FAILURE);
    }

    if(fork() == 0) //child
    {
        close(sockets[0]);
        worker(sockets[1]);
        return 0;
    }

    //parent
    close(sockets[1]);
    char buffer[MAX_MSG_SIZE];
    int size;
    while(scanf("%d", &size) > 0)
    {
        printf("Server sent %d bytes\n", size);
        write(sockets[0], buffer, size);
    }

    return 0;
}