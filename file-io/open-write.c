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

    int fd = open(argv[1], O_CREAT | O_WRONLY, S_IRWXU | S_IRWXG | S_IROTH);

    if(fd < 0)
    {
        fprintf(stderr, "Open Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    size_t stringLength = strlen(argv[2]) + 1;
    
    int var = write(fd, argv[2], stringLength);

    if(var < 0)
    {
        fprintf(stderr, "Write Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }    
    
    close(fd);

    return 0;
}
