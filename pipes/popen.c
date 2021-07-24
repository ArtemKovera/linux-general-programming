#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{   
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char buf[BUFSIZE];
    FILE *pipe = popen(argv[1], "r");

    if(pipe == NULL)
    {
        fprintf(stderr, "Some error occured in the popen()");
        exit(EXIT_FAILURE);
    }

    while(fgets(buf, BUFSIZE, pipe))
        puts(buf);

    pclose(pipe);

    return 0;
}