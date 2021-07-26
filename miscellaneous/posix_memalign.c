/*

    This example shows how to align data in heap using posix_memalign() function
    This program is analogous to one example from the course "Углубленное программирование на C/C++" by Алексей Петров

*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#define SIZE 10

int main()
{
    
    int arrayToCopy [SIZE] = {1, 2, [5] = 4, 7, 19, 25, 10};
    int *arrayInHeap = NULL;
    
    //the size of L1-data cache line
    long l1dc = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);

    if(l1dc == -1)  //if sysconf() has failed
    {
        l1dc = sizeof(void*);
    } 

    int errflag = posix_memalign((void**)&arrayInHeap, l1dc, sizeof arrayToCopy);

    if(!errflag) // if call to posix_memalign() is successful
    {
        memcpy(arrayInHeap, arrayToCopy, sizeof arrayToCopy);

        //printing arrayInHeap to the console
        for(size_t i = 0; i < SIZE; ++i)
            printf("arrayInHeap[i] = %d\n", arrayInHeap[i]);
        
        free(arrayInHeap);
    }
    else
    {
        fprintf(stderr, "Posix_memalign Error: %d\n", errflag);
        exit(EXIT_FAILURE);
    }
    
    return 0;
}