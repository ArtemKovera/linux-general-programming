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
#include<sys/select.h>
#include<fcntl.h>
#include<sys/epoll.h>

#define MAX_EVENTS 64


void makeNonblocking(int fd)
{
    int oldFlags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, oldFlags | O_NONBLOCK);
}


int main()
{
    int masterSocket = socket(AF_INET, SOCK_STREAM, 0);

         if(masterSocket == -1)
    {
        perror("socket()");
        exit(-1);
    }

    struct addrinfo hints;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

         struct addrinfo *bindAddress;

    getaddrinfo(0, "1234", &hints, &bindAddress);

    int status = bind(masterSocket, bindAddress->ai_addr, bindAddress->ai_addrlen);
    if(status == -1)
    {
        perror("bind()");
        exit(-1);
    }  

    makeNonblocking(masterSocket);

    listen(masterSocket, SOMAXCONN);

    int epoll = epoll_create1(0);

    struct epoll_event Event;

    Event.data.fd = masterSocket;
    Event.events = EPOLLIN;

    epoll_ctl(epoll, EPOLL_CTL_ADD, masterSocket, &Event);

    while(1)
    {   
        struct epoll_event Events[MAX_EVENTS];
        int N = epoll_wait(epoll, Events, MAX_EVENTS, -1);
        for(int i = 0; i < N; i++)
        {
            if(Events[i].data.fd == masterSocket)
            {
                int slaveSocket = accept(masterSocket, 0, 0);
                makeNonblocking(slaveSocket);
                struct epoll_event Event;
                Event.data.fd = slaveSocket;
                Event.events = EPOLLIN;
                epoll_ctl(epoll, EPOLL_CTL_ADD, slaveSocket, &Event);
            }
            else
            {
                static char buffer[1024];
                int recvBytes = recv(Events[i].data.fd, buffer, 1024, MSG_NOSIGNAL);
                if((recvBytes == 0) && (errno != EAGAIN))
                {
                    shutdown(Events[i].data.fd, SHUT_RDWR);
                    close(Events[i].data.fd);
                }
                else if(recvBytes > 0)
                {
                    send(Events[i].data.fd, buffer, recvBytes, MSG_NOSIGNAL);
                }
            }
        }
    }

    return 0;
}