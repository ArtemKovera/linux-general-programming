/*
    This little program demonstrates using fork() sys call
*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>


int main()
{
    pid_t pid = fork();
    
    if(pid==-1)
    {
        fprintf(stderr, "Some error occured in the fork()");
        return 1;
    }
    else if(pid==0)
    {
        printf("Hello from the child  with PID %d\n", getpid());
    }
    else
    {
        printf("Hello from the parent with PID %d\n", getpid());
        
    }

    return 0; 
}