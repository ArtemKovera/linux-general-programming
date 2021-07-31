#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


int main(int argc, char **argv)
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s <filename> <text_to_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int save, fd;

    save = dup(1);             //save stdout

    printf("now save is %d\n", save);

    fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);  
    
    if(fd < 0)
    {
        fprintf(stderr, "Error with opening %s\n", argv[1]);
    }

    dup2(fd, 1);              //to make the opened file standard output
     
    close(fd);                //close unnecessary file descriptor

    printf("%s\n", argv[2]);  //this text is supposed to be printed to the opened file

    dup2(save, 1);            //re-establish normal stdout

    close(save);              //close unnecessary file descriptor

    printf("This text is supposed to be printed to the console\n");

    return 0;
}