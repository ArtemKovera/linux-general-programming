/*
    This program is analogous to one example from the book "Linux System Programming: Talking Directly to the Kernel and C Library"
    by Robert Love
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

#define TIMEOUT 5
#define BUFFER_LENGTH 1024

int main()
{   
    struct timeval tv;
    fd_set readfds;
    int ret;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

    if(ret == -1)
    {
        perror("select");
        exit(EXIT_FAILURE);
    }
    else if (ret == 0)
    {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return 0;
    }
    
    if(FD_ISSET(STDIN_FILENO, &readfds))
    {
        char buf[BUFFER_LENGTH+1];
        int len;
        len = read(STDIN_FILENO, buf, BUFFER_LENGTH);

        if(len == -1)
        {
            perror("read");
            return 1;
        }

        if(len)
        {
            buf[len] = '\0';
            printf("read: %s\n", buf);
        }

        return 0;
    }
    
    fprintf(stderr, "This should not happen!\n");
    exit(EXIT_FAILURE);
}