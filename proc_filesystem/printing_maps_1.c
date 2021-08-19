/*  
    Printing to the console segments of a virtual memory of the process
    by using /poc/PID/maps
    Adapted from https://www.youtube.com/watch?v=VpygT3_61JQ&t
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<errno.h>

#define BUFF_SIZE 128

int main()
{
    int fdMe = open("printing_maps_1.c", O_RDONLY);
    if(fdMe == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char *sharedMemory = (char*) mmap(NULL, 100, PROT_READ, MAP_FILE | MAP_SHARED, fdMe, 0);

    char buf[BUFF_SIZE];

    sprintf(buf, "/proc/%d/maps", (int) getpid());

    int fd = open(buf, O_RDONLY);

    printf("%s\n", buf);

    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int nbyte;

    while((nbyte = read(fd, buf, sizeof(buf))) > 0)
        printf("%.*s", nbyte, buf);
    printf("\n"); 

    close(fd);
    munmap(sharedMemory, 100);
    close(fdMe);

    return 0;
}