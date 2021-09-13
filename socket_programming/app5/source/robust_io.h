/*
    The header for robust i/o functions
    The functions are analogous to the ones from the book "Computer Systems: A Programmer's Perspective"
    by Randal Bryant and David O'Hallaron
*/
#ifndef ROBUST_IO_H
#define ROBUST_IO_H
#include <stdio.h>

#define RIO_BUFSIZE 8192

typedef struct
{
    int  rioFd;
    int  rioCnt;
    char *rioBufPtr;
    char rioBuf[RIO_BUFSIZE];
} rioT;


//returns number of bytes transferred, 0 on EOF (rio_readn only), −1 on error
ssize_t rioReadn(int fd, void *userbuf, size_t n);

//returns number of bytes transferred, 0 on EOF (rio_readn only), −1 on error
ssize_t rioWriten(int fd, void *userbuf, size_t n);

//returns number of bytes transferred, 0 on EOF (rio_readn only), −1 on error
void rioReadInitb(rioT rp, int fd);

//returns number of bytes transferred, 0 on EOF (rio_readn only), −1 on error
ssize_t rioReadLineb(rioT rp, void *usrbuf, size_t maxlen);

//returns number of bytes transferred, 0 on EOF (rio_readn only), −1 on error
ssize_t rioReadnb(rioT rp, void *usrbuf, size_t n);

#endif