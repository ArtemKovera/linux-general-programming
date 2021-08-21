#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define FILE_PIPE "/tmp/named_pipe"
#define MESSAGE "MESSAGE FROM THE CLIENT"
#define MESSAGE_LEN 23

int main()
{
    puts("This is the client");
    
    int fd, wbytes;
    char *message = MESSAGE;

    fd = open(FILE_PIPE, O_WRONLY);         //opening pipe for writing
    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    //writing bytes to the pipe one by one
    size_t count = 0;
    while(1)
    {
        wbytes = write(fd, message, 1);

        if(wbytes == -1)
        {   
            if(errno = EINTR)
                continue;
            
            
            perror("write");
            exit(EXIT_FAILURE);
        }  

        count++;
        message++;

        if(count == MESSAGE_LEN)
           break;
    }


    puts("The message has been sent to the server");
    close(fd);

    return 0;
}