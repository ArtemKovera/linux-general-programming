#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void * foo(void *p)
{
    for(size_t i = 1; i < 5; ++i)
    {
        sleep(1);
        printf("Some text from foo() - %ld\n", i);
    }
    return NULL;
}

void * foo2(void *p)
{
    for(size_t i = 1; i < 7; ++i)
    {
        sleep(1);
        printf("Some text from foo2() - %ld\n", i);
    }
    return NULL;    
}

int main()
{
    pthread_t th1, th2;
    
    pthread_create(&th1, NULL, foo, NULL);

    puts("Some text from main()");

    pthread_create(&th2, NULL, foo2, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    puts("Some text from main() again");

    return 0;
}