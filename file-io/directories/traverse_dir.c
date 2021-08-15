/*
    This little program demonstrates how to traverse a current directory
    and get the total size of the files in this directory
    Adapted from https://www.youtube.com/watch?v=KddNStMQeo0&list=PLysdvSvCcUhbrU3HhGhfQVbhjnN9GXCq4&index=17
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<dirent.h>
#include<errno.h>

int main(int argc, char **argv)
{   

    DIR * directory = NULL;
    struct dirent * info = NULL; 
    struct stat sb;
    long int totalSize = 0;

    
    directory = opendir(".");
    
    if(directory == NULL)
    {
        perror("opendir()");
        exit(EXIT_FAILURE);
    }
    
    while((info = readdir(directory)) != NULL)
    {
        if(stat(info->d_name, &sb) != 0)
        {
            perror("stat()");
            exit(EXIT_FAILURE);
        }

        totalSize += sb.st_size;
    }

    printf("The total size of the files in the current directory is %ld bytes\n", totalSize);

    return 0;
}
