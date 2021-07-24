#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t pid;
    char buf;

    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) 
    {
        fprintf(stderr, "Some error occured in the pipe()");
        exit(EXIT_FAILURE);
    }

    pid = fork();
           
    if (pid == -1) 
    {
        fprintf(stderr, "Some error occured in the fork()");
        exit(EXIT_FAILURE);
    }

    
    if (pid == 0) //child 
    {    
        close(pipefd[1]);                     //close unused write end

        while (read(pipefd[0], &buf, 1) > 0)  //child reads from pipe
            write(STDOUT_FILENO, &buf, 1);    //child writes to stdout

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } 
    else //parent
    {            
        close(pipefd[0]);                           // close unused read end

        write(pipefd[1], argv[1], strlen(argv[1])); // parent writes argv[1] to pipe 

        close(pipefd[1]);                           //reader will see EOF

        wait(NULL);                                 //wait for child

        exit(EXIT_SUCCESS);
    }

    return 0;       
}