/*
    Adapted from https://www.youtube.com/watch?v=VpygT3_61JQ&t
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFF_SIZE 16
#define CMD "print(100 + 100)"
#define CMD_LEN 17

int main()
{
    int status;
    int fdToChild[2];

    if(pipe(fdToChild) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char buf[BUFF_SIZE];

    dup2(fdToChild[0], STDIN_FILENO); //read-end of the pipe

    status = fork();
    if(status == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(status == 0) //child
    {
        close(fdToChild[1]);
        execlp("python3", "python3", "-i", NULL); 
    } 

    //parent
    close(fdToChild[0]);

    status = write(fdToChild[1], CMD, CMD_LEN);
    if(status == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fdToChild[1]);
    wait(NULL);

    return 0;
}