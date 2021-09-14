/*
    Robust i/o functions implementations
    The functions are analogous to the ones from the book "Computer Systems: A Programmer's Perspective"
    by Randal Bryant and David O'Hallaron
*/
#include"robust_io.h"
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

//-----------------------------------------------------
//Unbuffered input and output functions

ssize_t rioReadn(int fd, void *userbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = userbuf;

    while(nleft > 0)
    {
        if((nread = read(fd, bufp, nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;
            else
                return -1;    
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    
    return (n - nleft);
}

ssize_t rioWriten(int fd, void *userbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = userbuf;

    while(nleft > 0)
    {
        if((nwritten = write(fd, bufp, nleft)) <= 0)
        {
            if(errno == EINTR)
                nwritten = 0;
            else
                return -1;  
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

//------------------------------------------------------
//Buffered input functions

void rioReadInitb(rioT *rp, int fd)
{
    rp->rioFd = fd;
    rp->rioCnt = 0;
    rp->rioBufPtr = rp->rioBuf;    
}

static ssize_t rioRead(rioT *rp, char *usrbuf, size_t n)
{
    int cnt;

    while(rp->rioCnt <= 0)
    {
        rp->rioCnt = read(rp->rioFd, rp->rioBuf, sizeof(rp->rioBuf));
        if(rp->rioCnt < 0)
        {
            if(errno != EINTR)
                return -1;
        }
        else if(rp->rioCnt == 0)
            return 0;
        else   
            rp->rioBufPtr = rp->rioBuf; 
    }   

    cnt = n;
    if(rp->rioCnt < n)
        cnt = rp->rioCnt;
    
    memcpy(usrbuf, rp->rioBufPtr, cnt);
    rp->rioBufPtr += cnt;
    rp->rioCnt -= cnt;
    return cnt;
}


ssize_t rioReadLineb(rioT *rp, void *usrbuf, size_t maxlen)
{
    int n, rc;
    char c;
    char *bufp = usrbuf;

    for(n = 1; n < maxlen; n++)
    {
        if((rc = rioRead(rp, &c, 1)) == 1)
        {
            *bufp++ = c;
            if(c == '\n')
            {
                n++;
                break;
            }
        }
        else if(rc == 0)
        {
            if(n == 1)
                return 0;
            else
                break;   
        }
        else
            return -1;  
    }
    *bufp = 0;
    return n-1;
}

ssize_t rioReadnb(rioT *rp, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0)
    {
        if((nread = rioRead(rp, bufp, nleft)) < 0)
            return -1;
        else if(nread == 0)
            break;
        nleft -= nread;
        bufp += nread;
    }
    
    return (n - nleft);
}