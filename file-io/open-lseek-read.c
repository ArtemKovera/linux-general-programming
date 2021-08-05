#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define BUFFER_SIZE 1024
#define BYTES_TO_READ 20
#define SHIFT 16

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    
    if(fd == -1)
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    int lsk = lseek(fd, 0, SEEK_END);

    if(lsk == -1)
    {
        perror("1st lseek()");
        exit(EXIT_FAILURE);        
    }

    printf("The siza of the file %s is %d bytes\n", argv[1], lsk);

    lsk = lseek(fd, SHIFT, SEEK_SET);

    if(lsk == -1)
    {
        perror("2d lseek()");
        exit(EXIT_FAILURE);        
    } 

    char buf [BUFFER_SIZE] = {'\0'};
    size_t bytesToRead = BYTES_TO_READ;
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