#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>

const size_t STACK_SIZE = 1024*1024*16;

void *foo(void *arg)
{
    printf("Hi from the thread with a stack size %ld bytes\n", STACK_SIZE);
    return NULL;
}

int main()
{
    pthread_t thread;
    pthread_attr_t attr;
    int errflag;

    errflag = pthread_attr_init(&attr);

    if(errflag != 0)
    {
        fprintf(stderr, "Error with initializing attributes\n");
        exit(EXIT_FAILURE);
    }

    //setting stack size
    errflag = pthread_attr_setstacksize(&attr, STACK_SIZE);

    if(errflag != 0)
    {
        fprintf(stderr, "Error with setting the stack size attribute\n");
        exit(EXIT_FAILURE);
    }
    
    errflag = pthread_create(&thread, NULL, foo, NULL);

    if(errflag != 0)
    {
        fprintf(stderr, "Error with creating the thread\n");

        switch (errflag)
        {
            case EINVAL:
                fprintf(stderr, "Anappropriate attributes for the thread\n");
                break;
            case EAGAIN:
                fprintf(stderr, "Insufficient resources to create the thread\n");
                break;
            case EPERM:
                fprintf(stderr, "No permission to set the scheduling policy and parameters specified in attr\n");
                break;
        }

        exit(EXIT_FAILURE);
    }

    pthread_attr_destroy(&attr);

    pthread_exit(NULL);

    return 0;
}