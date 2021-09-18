/*
    An echo server.
    The code is analogous to one example from the book "Computer Systems: A Programmer's Perspective"
    by Randal Bryant and David O'Hallaron
*/
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include"robust_io.h"

void echo(int connfd);

int main(int argc, char **argv)
{

    return 0;
}