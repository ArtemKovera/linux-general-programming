#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define FILE_PIPE "/tmp/named_pipe"
#define MODE 0666
#define BUFF_SIZE 256

int main()
{
    puts("This is the server");

    int status, fd, rbytes;
    char ch;
    
    status = mkfifo(FILE_PIPE, MODE);
    if(status == -1)
    {   
        if(errno = EEXIST)
        {
            puts("this named pipe already exists, which is fine");
        }
        else
        {
            perror("mkfifo");
            exit(EXIT_FAILURE);            
        }
    }

    fd = open(FILE_PIPE, O_RDONLY);         //opening pipe for reading
    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    char buffer[BUFF_SIZE] = {0};
    char *pointer = buffer;
    
    //reading bytes from the pipe one by one
    
    while(1)
    {
        rbytes = read(fd, pointer, 1);
        if(rbytes == -1)
        {   
            if (errno == EINTR)       //if read intrrupted by some signal continue
                continue;
            
            perror("read");
            exit(EXIT_FAILURE);
        }
        if(rbytes == 0)
            break;

        pointer++;
    }

    puts("The message from the client: ");
    printf("%s\n", buffer);
    close(fd);

    return 0;
}