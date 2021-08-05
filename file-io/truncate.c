#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>


int main(int argc, char **argv)
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s <file_name> <length>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    off_t length = atol(argv[2]);
        
    int rflag = truncate(argv[1], length);

    if(rflag == -1)
    {
        perror("Error with truncate()");
        exit(EXIT_FAILURE);        
    }

    return 0;
}