#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "usege: %s <directory_name> \n", argv[0]);
        exit(EXIT_FAILURE);   
    } 

    int errflag = rmdir(argv[1]);

    if(errflag == -1)
    {
        perror("mkdir()");
        exit(EXIT_FAILURE);
    }

    return 0;    
}