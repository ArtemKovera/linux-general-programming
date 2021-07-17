#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>


int main()
{   
    errno = 0;
    long number = sysconf(_SC_CHILD_MAX);

    if(number == -1)
    {
        if(errno == 0)
        {
            fprintf(stderr, "sysconf considers _SC_CHILD_MAX unsupported\n");
        }
        else
        {
            fprintf(stderr, "sysconf failure\n");
            perror("sysconf");
        }  
        exit(EXIT_FAILURE);
    }


    printf("According to sysconf(_SC_CHILD_MAX), the maximum number of simultenious processes per user ID is %ld\n", number);

    return 0;
}