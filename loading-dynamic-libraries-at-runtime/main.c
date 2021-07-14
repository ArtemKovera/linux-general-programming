#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>


int main(int argc, char **argv)
{
    if(argc < 6)
    {
        fprintf(stderr, "Error: too few command line arguments to the program\n");
        exit(EXIT_FAILURE);
    }
    
    // based on command line arguments
    const char *pathToLibrary = argv[1];
    const char *functionName  = argv[2];
    const int number1         = atoi(argv[3]);
    const int number2         = atoi(argv[4]);
    const int number3         = atoi(argv[5]);

    //handler for working with a dynamic library
    void *handler = dlopen(pathToLibrary, RTLD_LAZY);
    
    //checking if dlopen works
    if(handler==NULL)
    {
        perror("dlopen");
        exit(EXIT_FAILURE);
    }
        
    
    //function pointer for working with a function in a library
    int (*fPointer) (int, int, int) = dlsym(handler, functionName);


    //checking if dlsym works
    if(fPointer == NULL)
    {   
        perror("dlsym");
        exit(EXIT_FAILURE);
    }

    //actual work
    printf("The result = %d", fPointer(number1, number2, number3));

    //closing the library
    dlclose(handler);

    return 0;
}