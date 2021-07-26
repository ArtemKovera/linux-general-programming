#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main()
{   
    errno = 0;
    long cacheSize1D = sysconf(_SC_LEVEL1_DCACHE_SIZE);

    if(cacheSize1D == -1)
    {
        if(errno == -1)
        {
            fprintf(stderr, "sysconf considers _SC_LEVEL1_DCACHE_SIZE unsupported\n");
        }
        else
        {
            fprintf(stderr, "sysconf failure\n");
            perror("sysconf");
        }  
        exit(EXIT_FAILURE);  
    }

    printf("According to sysconf(_SC_LEVEL1_DCACHE_SIZE), the cache 1-l data size is %ld bytes\n", cacheSize1D);

    errno = 0;
    long cacheSize1I = sysconf(_SC_LEVEL1_ICACHE_SIZE);

    if(cacheSize1I == -1)
    {
        if(errno == -1)
        {
            fprintf(stderr, "sysconf considers _SC_LEVEL1_ICACHE_SIZE unsupported\n");
        }
        else
        {
            fprintf(stderr, "sysconf failure\n");
            perror("sysconf");
        }  
        exit(EXIT_FAILURE);  
    }

    printf("According to sysconf(_SC_LEVEL1_ICACHE_SIZE), the cache 1-l instruction size is %ld bytes\n", cacheSize1I);


    errno = 0;
    long cacheLine1D = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    
    if(cacheLine1D == -1)
    {
        if(errno == 0)
        {
            fprintf(stderr, "sysconf considers _SC_LEVEL1_DCACHE_LINESIZE unsupported\n");
        }
        else
        {
            fprintf(stderr, "sysconf failure\n");
            perror("sysconf");
        }  
        exit(EXIT_FAILURE);        
    }

    printf("According to sysconf(_SC_LEVEL1_DCACHE_LINESIZE), the cache line 1-l data size is %ld bytes\n", cacheLine1D);


    errno = 0;
    long cacheLine1I = sysconf(_SC_LEVEL1_ICACHE_LINESIZE);

       if(cacheLine1I == -1)
    {
        if(errno == 0)
        {
            fprintf(stderr, "sysconf considers _SC_LEVEL1_ICACHE_LINESIZE unsupported\n");
        }
        else
        {
            fprintf(stderr, "sysconf failure\n");
            perror("sysconf");
        }  
        exit(EXIT_FAILURE);        
    }

    printf("According to sysconf(_SC_LEVEL1_ICACHE_LINESIZE), the cache line 1-l instruction size is %ld bytes\n", cacheLine1I);

    return 0;
}