/*
    This little program demonstrates using the clone() sys call
    This program is analogous to an example from the course "Основы программирования для Linux" by Кирилл Кринкин
*/
#include<sched.h>
#include<stdio.h>
#include<unistd.h>

#define STACK_SIZE 10000
char child_stack[STACK_SIZE+1];

int child(void *parameters)
{
    int count = 0;
    while(1)
    {
        sleep(1);
        printf("child's turn %d\n", count++);
    }

    return 0;
}

int main()
{
    int count = 0;
    int threadID = clone(child, child_stack+STACK_SIZE, 0, 0);

    if(threadID==-1)
    {
        fprintf(stderr, "some problem occur calling clone()\n");
        return 1;
    }

    printf("Thread ID (PID) = %d\n", threadID); 
   
    while(1)
    {
        sleep(1);
        printf("parent's turn %d\n", count++);
    }

    return 0;
}