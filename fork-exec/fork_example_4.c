#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main()
{
    pid_t p1 = fork();
    if(p1 == -1)
    {
        perror("Fork()");
        exit(EXIT_FAILURE);
    }

    if(p1 == 0)
    {
        puts("Child process -");
        sleep(1);
        puts("Child process --");
        sleep(1);
        puts("Child process ---");
        return 0;
    }
    else
    {
        pid_t p2 = 0;

        do
        {
            p2 = waitpid(-1, NULL, WNOHANG);
            sleep(1);
            puts("waiting for the child...");
        }
        while(p2 == 0); 
    }
    
    puts("Finish");
    return 0;
}