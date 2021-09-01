/*
    This program is analogous to one example from the book "Linux System Programming: Talking Directly to the Kernel and C Library"
    by Robert Love
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<poll.h>
#include<errno.h>

#define TIMEOUT 5

int main()
{
    struct pollfd fds[2];
    int ret;

    //watch stdin for input
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    //watch stdout for ability to write
    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;

    ret = poll(fds, 2, TIMEOUT * 1000);
    if(ret == -1)
    {
        perror("poll");
        exit(EXIT_FAILURE);
    }
    
    if(!ret)
    {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return 0;
    }

    if(fds[0].revents & POLLIN)
        printf("stdin is readable\n");
    
    if(fds[1].revents & POLLOUT)
        printf("stdout is writable\n");
    
    return 0;
}