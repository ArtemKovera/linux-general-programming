#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define ARRAY_SIZE 10

void * foo (void * arg)
{   
    size_t size = * (size_t *) arg;
    int *array = (int*) malloc(size * sizeof(int));

    for(size_t i = 0; i < size; ++i)
        array[i] = i;
    
    return array;
}

int main()
{
    pthread_t th1;
    int * array = NULL;
    size_t arraySize = ARRAY_SIZE;
    
    pthread_create(&th1, NULL, foo, &arraySize);
    pthread_join(th1, (void *)&array);

    for(size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        printf("array[%ld] = %d\n", i, array[i]);
    }
    
    free(array);
    return 0;
}