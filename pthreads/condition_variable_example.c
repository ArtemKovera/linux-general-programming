#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

#define COUNT 10

pthread_cond_t condVar;
pthread_mutex_t mutex;
int globalVar;


void * foo1(void * arg)
{
    for(int i = 0; i < COUNT; ++i)
    {   
        pthread_mutex_lock(&mutex);
        globalVar += 10;
        printf("globalVar after increasing = %d\n", globalVar);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condVar);
        sleep(1);
    }

    return NULL;
}

void * foo2(void * arg)
{   
    pthread_mutex_lock(&mutex);
    while(globalVar < 30) //ensuring that globalVar is never less than 0
    {
        pthread_cond_wait(&condVar, &mutex);
    }
    globalVar -= 30;
    printf("globalVar after decreasing = %d\n", globalVar);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t th1;
    pthread_t th2;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condVar, NULL);

    pthread_create(&th1, NULL, foo1, NULL);
    pthread_create(&th2, NULL, foo2, NULL);


    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condVar);

    return 0;
}