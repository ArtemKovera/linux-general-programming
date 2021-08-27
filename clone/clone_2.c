/*
    This little program demonstrates using the clone() sys call
    to make a new thread of execution
*/
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define _GNU_SOURCE  
#include<linux/sched.h>
#include<errno.h>

#define STACK_SIZE 64*1024

volatile bool isFinished = false;

int flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD;

int foo(void *arg)
{   
    printf("PID = %d, ID of the new  thread = %d\n", getpid(), gettid());
    isFinished = true;
    return 0;
}

int main()
{
    pid_t threadID;

    void *stack = malloc(STACK_SIZE);
    void *stackTop = stack + STACK_SIZE;
    printf("PID = %d, ID of the main thread = %d\n", getpid(), gettid());

    threadID = clone(foo, stackTop, flags, 0);

    if(threadID == -1)
    {
        perror("clone");
        exit(EXIT_FAILURE);
    }
    
    while( !isFinished )
        sched_yield();
    
    free(stack);
    return 0;
}