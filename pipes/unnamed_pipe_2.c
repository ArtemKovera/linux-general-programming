/*
    The behaviour of this program is equivalent to "ls | sort -r"
    Adapted from https://www.youtube.com/watch?v=vqmwpFJxGo8&list=PLysdvSvCcUhbrU3HhGhfQVbhjnN9GXCq4&index=34
*/
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>


int main()
{
    int pipeFD[2];

    pipe(pipeFD);

    if(fork() == 0)
    {
        //Child. Connect stdout to pipe
        dup2(pipeFD[1], STDOUT_FILENO);
        close(pipeFD[0]);
        execlp("ls", "ls", NULL);
    }    
    
    //Parent. Connect stdin to pipe
    dup2(pipeFD[0], STDIN_FILENO);
    close(pipeFD[1]);
    execlp("sort", "sort", "-r", NULL);

    return 0;
}