#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

#define SIZE 4 

void *threadFunc(void *arg)
{
    printf("Thread - %ld\n", pthread_self());
    return NULL;
}

int main()
{
    pthread_t threadArray [SIZE];
    
    for(size_t i = 0; i < SIZE; ++i)
    {
        pthread_create(&threadArray[i], NULL, threadFunc, NULL);
    }

    for(size_t i = 0; i < SIZE; ++i)
    {
        pthread_join(threadArray[i], NULL);
    }
    
    return 0;
}