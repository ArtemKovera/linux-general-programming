#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
if(argc < 3)
    {
        fprintf(stderr, "usege: %s <filename> <text_to_file>\n", argv[0]);
        exit(EXIT_FAILURE);   
    }

    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU | S_IRWXG | S_IROTH);

    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    size_t stringLength = strlen(argv[2]) + 1;
    
    while(1)
    {
        ssize_t var = write(fd, argv[2], stringLength);

        if(var == -1)
        {
            if(errno == EINTR)
                continue;

            break;
            perror("write");
            exit(EXIT_FAILURE);
        } 

        break;        
    }

    
    if (fsync(fd) == -1)
    {
        perror("fsync");
        exit(EXIT_FAILURE);
    }

    close(fd);    
    return 0;
}