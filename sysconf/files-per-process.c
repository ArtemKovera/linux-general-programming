#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main()
{   
    errno = 0;
    long number = sysconf(_SC_OPEN_MAX);

    if(number == -1)
    {
        if(errno == 0)
        {
            fprintf(stderr, "sysconf considers _SC_OPEN_MAX unsupported\n");
        }
        else
        {
            fprintf(stderr, "sysconf failure\n");
            perror("sysconf");
        }  
        exit(EXIT_FAILURE);
    }


    printf("According to sysconf(_SC_OPEN_MAX), the maximum number of open files per process is %ld\n", number);

    return 0;
}