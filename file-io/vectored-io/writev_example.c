/*
    This program is analogous to one example from the book "Linux System Programming: Talking Directly to the Kernel and C Library"
    by Robert Love
*/
#include<sys/uio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define LINES 3

int main()
{
    struct iovec iov[LINES];
    ssize_t writtenBytes;
    int fd, i;

    char *buf[] = { "Line one\n",
                    "Line two\n",
                    "Line three\n" };
    
    fd = open ("file.txt", O_WRONLY | O_CREAT | O_TRUNC);
    
    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < LINES; i++)
    {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]) + 1;        
    }

    writtenBytes = writev(fd, iov, LINES);
    if (writtenBytes == -1)
    {
        perror ("writev");
        exit(EXIT_FAILURE);
    }

    printf ("%ld bytes have been written\n", writtenBytes);
    if (close (fd)) 
    {
        perror ("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}