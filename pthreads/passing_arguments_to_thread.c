#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void * foo (void * arg)
{
    * (int *)arg += 100;

    return NULL;
}

void * foo2 (void * arg)
{
    * (double *)arg *= 1024;
    
    return NULL;
}

void * foo3 (void * arg)
{   
    char * ch = (char *) arg;
    while(*ch != '\0')
    {
        * ch += 1;
        ch++;
    }
        
    return NULL;    
}

int main()
{
    int varInt = 100;
    double varDoub = 2.0;
    char string [] = "abc";

    pthread_t th1, th2, th3;
    
    printf("varInt before the thread  = %d\n", varInt);
    printf("varDoub before the thread = %f\n", varDoub);
    printf("string  before the thread = %s\n\n", string);

    pthread_create(&th1, NULL, foo, &varInt);
    pthread_create(&th2, NULL, foo2, &varDoub);
    pthread_create(&th3, NULL, foo3, &string);
    
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);

    printf("varInt after the thread   = %d\n", varInt);
    printf("varDoub after the thread  = %f\n", varDoub);
    printf("string  after the thread  = %s\n", string);

    return 0;
}