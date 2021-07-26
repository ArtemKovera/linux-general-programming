#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

#define COUNT 100

typedef struct 
{
    pthread_mutex_t mutex;
    int variable; 

} SharedStruct;

void * foo (void* arg)
{
    SharedStruct* st = (SharedStruct*) arg;
    pthread_mutex_t *mutex = &(st->mutex);

    //locking the mutex
    int errflag = pthread_mutex_lock(mutex);
    if(errflag != 0)
    {
        fprintf(stderr, "Error with mutex locking in foo()\n");
        exit(EXIT_FAILURE);
    }
    
    //changing the data
    for(size_t i = 0; i < COUNT; ++i)
        st->variable++;

    
    //unlocking the mutex
    errflag = pthread_mutex_unlock(mutex);
    if(errflag != 0)
    {
        fprintf(stderr, "Error with mutex ulocking in foo()\n");
        exit(EXIT_FAILURE);
    }  

    return NULL;  
}

int main()
{
    SharedStruct shSt = {PTHREAD_MUTEX_INITIALIZER, 0};
    pthread_t thread;

    int errflag = pthread_create(&thread, NULL, foo, &shSt);
    if(errflag != 0)
    {
        fprintf(stderr, "Error with thread creation\n");
        exit(EXIT_FAILURE);        
    }

    //changing the data in main()
    for(size_t i = 0; i < COUNT; ++i)
        shSt.variable++;    
        

    errflag = pthread_join(thread, NULL);
    if(errflag != 0)
    {
        if(errflag == ESRCH)
        {
            fprintf(stderr, "No thread with %ld ID can be found\n", thread);
            exit(EXIT_FAILURE);
        }
        else if (errflag == EINVAL)
        {
            fprintf(stderr, "The thread %ld is not joinable\n", thread);
            exit(EXIT_FAILURE);            
        }
        else
        {
            exit(EXIT_FAILURE);
        }        
    }

    //checking the data (it must be 200)
    printf("The varible = %d\n", shSt.variable);

    return 0;
}