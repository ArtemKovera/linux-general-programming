#include<sys/mman.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

#define PAGESIZE 4096

int main()
{

    long pageSize = sysconf(_SC_PAGE_SIZE);     //virtual memory page size

    if(pageSize == -1)
    {
        pageSize = PAGESIZE;
    }
    
    //allocating memory
    void *address = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if(address == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("%ld bytes have been allocated at %p with mmap() sys call\n", pageSize, address);
    
    //deallocating memory
    int status = munmap(address, pageSize);

    if(status == -1)
    {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    
    printf("This memory has been deallocated with munmap() sys call\n");
    address = NULL;

    return 0;
}