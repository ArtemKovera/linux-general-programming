/*
    Program demonstrating how to copy a file with sendfile()
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/sendfile.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s <file_source> <file_destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int source, destination, result;
    
    source = open(argv[1], O_RDONLY);
    if(source == -1)
    {
        perror("open (source file)");
        exit(EXIT_FAILURE);
    }

    destination = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG | S_IROTH);
    if(destination == -1)
    {
        perror("open (destination file)");
        close(source);
        exit(EXIT_FAILURE);
    }

    struct stat stbuf;

    if(fstat(source, &stbuf) == -1)
    {
        perror("fstat");
        exit(EXIT_FAILURE);
    }
    
    while(1)
    {
        result = sendfile(destination, source, 0, stbuf.st_size);
        if(result == -1)
        {
            perror("sendfile");
            exit(EXIT_FAILURE);
        }

        if(result < stbuf.st_size)
            continue;  

        break;      
    }


    close(source);
    close(destination);

    return 0;
}