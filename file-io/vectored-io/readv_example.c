/*
    This program is analogous to one example from the book "Linux System Programming: Talking Directly to the Kernel and C Library"
    by Robert Love
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define LINE1_LEN 10
#define LINE2_LEN 10
#define LINE3_LEN 12

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char lin1[LINE1_LEN], lin2[LINE2_LEN], lin3[LINE3_LEN];
    struct iovec iov[3];
    ssize_t readBytes;
    int fd, i;

    fd = open(argv[1], O_RDONLY);
    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    iov[0].iov_base = lin1;
    iov[0].iov_len = sizeof (lin1);
    iov[1].iov_base = lin2;
    iov[1].iov_len = sizeof (lin2);
    iov[2].iov_base = lin3;
    iov[2].iov_len = sizeof (lin3);

    readBytes = readv (fd, iov, 3);
    if(readBytes == -1)
    {
        perror("readv");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 3; i++)
        printf ("%d: %s", i+1, (char *) iov[i].iov_base);

    if (close (fd)) 
    {
        perror ("close");
        exit(EXIT_FAILURE);
    }    

    return 0;
}