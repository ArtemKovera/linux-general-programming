#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main()
{   
    errno = 0;
    long pageSize = sysconf(_SC_PAGE_SIZE);

    if(pageSize == -1)
    {
        if(errno == 0)
        {
            fprintf(stderr, "sysconf considers _SC_PAGE_SIZE unsupported\n");
        }
        else
        {
            fprintf(stderr, "sysconf failure\n");
            perror("sysconf");
        }  
        exit(EXIT_FAILURE);
    }


    printf("According to sysconf(_SC_PAGE_SIZE), the page size is %ld bytes\n", pageSize);

    return 0;
}