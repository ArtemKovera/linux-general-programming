/*
    This little program demonstrates using fork() and wait() sys calls
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


int main()
{
    pid_t pid = fork();

    if(pid==-1)
    {
        fprintf(stderr, "some error occured with calling fork()\n");
        return -1;
    }
    
    if(pid==0)
    {
        printf("something is happening in the child with PID %d\n", getpid());
        sleep(2);
        exit(0);
    }
    
    int status = 0;
    pid_t childPid = wait(&status);
    printf("the parent waits for the child (%d)\n", childPid);
    printf("the child's return value was %d\n", WEXITSTATUS(status));
    
    return 0;
}