/*
   This program is analogous to one example from an online seminar by Nikolay Efanov
   https://www.youtube.com/watch?v=CKgvjrDqriY&t
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<errno.h>

#define TIMEOUT 5000
#define SIZE 5
#define BUFF_SIZE 4096

int main()
{
    struct epoll_event evn;
    struct epoll_event events[SIZE];
    int lenRd;
    char buff[BUFF_SIZE];

    int epoll_fd = epoll_create1(STDIN_FILENO);
    if(epoll_fd == -1)
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    evn.events = EPOLLIN;
    evn.data.fd = STDIN_FILENO;

    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &evn))
    {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }

    int i;
    int event_count = epoll_wait(epoll_fd, events, SIZE, TIMEOUT);
    if(event_count == -1)
    {
        perror("epoll_wait");
        exit(EXIT_FAILURE);
    }
    else if(event_count == 0)
    {
        printf("Timeout\n");
    }
    else
    {
        for(i=0; i < event_count; ++i)
        {
            printf("Handling file descriptor: %u\n", events[i].data.fd);
            lenRd = read(events[i].data.fd, buff, BUFF_SIZE);
            if(lenRd == -1)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }
            buff[lenRd] = '\0';
            printf("%s", buff);
        }
    }
    
    if(close(epoll_fd))
    {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}