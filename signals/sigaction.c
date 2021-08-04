#include<stdio.h>
#include<signal.h>
#include<unistd.h>

#define MESSAGE "SIGINT doesn't work. Try something else\n"

static void signalHandler(int num)
{
    write(STDOUT_FILENO, MESSAGE, sizeof(MESSAGE) - 1);     
}

int main()
{
    struct sigaction SA;
    SA.sa_handler = signalHandler;
    int count = 0;
    
    sigaction(SIGINT, &SA, NULL);

    while(1)
    {
        printf("I'm %d. I can count to %d\n", getpid(), count);
        count++;
        sleep(1);
    }

    return 0;
}