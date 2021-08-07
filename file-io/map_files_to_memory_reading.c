#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int fd;
    
    fd = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR);
    
    if(fd < 0)
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }
    
    struct stat st; 

    if(fstat(fd, &st) == -1)
    {
        perror("coudn't get the file's size");
        exit(EXIT_FAILURE);
    }
    
    printf("The size of the file %s is %ld\n", argv[0], st.st_size);

    char *fileInMemory = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    

    //printing the file to the console
    for(size_t i = 0; i < st.st_size; ++i)
    {
        putchar(fileInMemory[i]);
    }
    
    munmap(fileInMemory, st.st_size);
    close(fd);

    return 0; 
}