/*  
    A function for establishing a connection with a server. 
    It returns an open socket descriptor that is ready for
    input and output.

    This function is analogous to one from the book "Computer Systems: A Programmer's Perspective"
    by Randal Bryant and David O'Hallaron    
*/
#ifndef _OPEN_CLIENT_FD_
#define _OPEN_CLIENT_FD_

int openClientFD(const char* hostname, const char* port);

#endif