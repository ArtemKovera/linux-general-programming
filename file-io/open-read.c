#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LEN 1024

int main(int argc, char **argv)
{   
    if(argc < 3)
    {
        fprintf(stderr, "usege: %s <filename> <number_of_bytes_to_read>\n", argv[0]);
        exit(EXIT_FAILURE);   
    }

    int fd = open(argv[1], O_RDONLY);

    if(fd < 0)
    {
        fprintf(stderr, "Open Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char buf [LEN] = {'\0'};
    size_t bytesToRead = atoi(argv[2]);
    ssize_t bytesRead;
    size_t index = 0;

    while (bytesToRead != 0 && (bytesRead = read(fd, &buf[index], bytesToRead)) != 0)
    {
        if(bytesRead == -1)
        {
            if(errno == EINTR)
                continue;
            
            perror("read");
            break;
        }
        
        bytesToRead -= bytesRead;
        index += bytesRead;
    }

    printf("The read characters from the file \"%s\":\n%s\n", argv[1], buf);

    if (close (fd) == -1)
        perror ("close()");
    
    return 0;
}
