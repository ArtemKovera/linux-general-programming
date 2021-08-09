#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "usege: %s <directory_name> \n", argv[0]);
        exit(EXIT_FAILURE);   
    }    
    
    int errflag = mkdir(argv[1], S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IXUSR | S_IXGRP | S_IXOTH);

    if(errflag == -1)
    {
        perror("mkdir()");
        exit(EXIT_FAILURE);
    }

    return 0;
}