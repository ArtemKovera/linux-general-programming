#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>

void *fooDetached(void *arg)
{
    printf("It's a detached thread. Its ID is %ld\n", pthread_self());
    pthread_exit(NULL);
}

int main()
{   
    int errflag;
    pthread_t detachedTread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    errflag = pthread_create(&detachedTread, &attr, fooDetached, NULL);
    if(errflag != 0)
    {
        fprintf(stderr, "Error in mai() with creating a thread\n");
        exit(EXIT_FAILURE);        
    }
    
    //demonstrating unjoinability of the thread
    errflag = pthread_join(detachedTread, NULL);
    if(errflag == EINVAL)
    {
        printf("This thread with ID %ld is NOT joinable\n", detachedTread);
    }
    else if (errflag == ESRCH)
    {
        fprintf(stderr, "There is no thread with this ID %ld\n", detachedTread);
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(stderr, "Some error with pthread_join()\n");
        exit(EXIT_FAILURE);
    }
    
    sleep(1);
    puts("exeting the main thread");

    return 0;
}