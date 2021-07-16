/*
    This is a program for a simple Unix shell.
    This program is analogous to the one from "Advanced Programming in the UNIX Environment" course
    https://www.youtube.com/watch?v=w3spRzZ8bSA&list=PL0qfF8MrJ-jxMfirAdxDs9zIiBg2Wug0z&index=3
*/
#include<sys/types.h>
#include<sys/unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *getUserInput(char *buff, size_t len)
{
    printf("$$");
    return fgets(buff, len, stdin);
}

int main(int argc, char **argv)
{
    char buffer[BUFSIZ];
    pid_t pid;
    int status;

    (void)argc;
    (void)argv;

    while(getUserInput(buffer, sizeof(buffer)))
    {
        buffer[strlen(buffer) - 1] = '\0';
   
    
        if( (pid = fork()) == -1)
        {
            fprintf(stderr, "shell can't fork: %s\n", strerror(errno));
            continue;
        }
        else if (pid == 0)
        {
            execlp(buffer, buffer, NULL);
            fprintf(stderr, "shell can't exec: %s %s \n", buffer, strerror(errno));
            exit(EXIT_FAILURE);
        }

        if((pid=waitpid(pid, &status, 0)) < 0)
        {
            fprintf(stderr, "shell waitpid error: %s\n", strerror(errno));
        }
         
    }


    return 0;
}