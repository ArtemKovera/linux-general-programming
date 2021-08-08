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
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s <file> <new_text_to_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int fd;
    
    fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
    
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

    char *fileInMemory = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    char *pt = argv[2];

    //writing new text to the file
    while(*pt != '\0')
    {
        *fileInMemory = *pt;
        fileInMemory++;
        pt++;
    }
    
    munmap(fileInMemory, st.st_size);
    close(fd);

    return 0; 
}