/*
    how to create 2 child processes 
    how to send signal to other process
    how to use waitpid() and how to get childs'
    status information with dedicated macros
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>


int main(int argc, char **argv)
{
    pid_t pid1, pid2, w1, w2;
    int status1, status2;

    pid1 = fork();   // creating 1st child
    if(pid1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if(pid1 == 0)
    {
        printf("1st child starts...\n");
        sleep(5);                         //this process is supposed to be killed by a signal
        return 0;
    }
    //////////
    
    pid2 = fork();  // creating 2nd child
    if(pid2 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }  

    if(pid2 == 0)
    {
        printf("2nd child starts\n");

        if((kill(pid1, SIGKILL)) == -1) //sending SIGKILL to Child1
        {
            perror("kill");
            exit(EXIT_FAILURE);
        } 

        printf("2nd child terminates shortly\n");
        return 0;
    }
    /////////
    

    w1 = waitpid(pid1, &status1, 0);
    if(w1 == -1)
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    if(WIFEXITED(status1))
    {
        printf("Child1 exited with status %d\n", WEXITSTATUS(status1));
    }
    else if(WIFSIGNALED(status1))
    {
        printf("Child1 killed by signal %d\n", WTERMSIG(status1));
    }
    else if(WIFSTOPPED(status1))
    {
        printf("Child1 stopped by signal %d\n", WSTOPSIG(status1));
    }
    else if(WIFCONTINUED(status1))
    {
       printf("Child1 continued\n"); 
    }
    
    w2 = waitpid(pid2, &status2, 0);
    if(w1 == -1)
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    } 

    if(WIFEXITED(status2))
    {
        printf("Child2 exited with status %d\n", WEXITSTATUS(status2));
    }
    else if(WIFSIGNALED(status2))
    {
        printf("Child2 killed by signal %d\n", WTERMSIG(status2));
    }
    else if(WIFSTOPPED(status2))
    {
        printf("Child2 stopped by signal %d\n", WSTOPSIG(status2));
    }
    else if(WIFCONTINUED(status2))
    {
       printf("Child2 continued\n"); 
    }

    return 0;
}