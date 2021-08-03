/*
    This little program demonstrates using exec() sys call without using fork()
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: <program> <text_to_print>\n");
        exit(EXIT_FAILURE);
    }
    
    int errflag = execv("/bin/echo", argv);

    if(errflag == -1)
    {
        fprintf(stderr, "Error with execv()\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}