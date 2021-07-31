/*
    This program is analogous to one example from the book "Программирование: введение в профессию. Том 3: системы и сети"
    by Андрей Викторович Столяров
*/
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

#define TIMES 10
#define SLEEP 500000

volatile static sig_atomic_t count = 0;
const char message[] = "Press it again\n";

void signalHendler(int sig)
{
    int saveErrno = errno;
    signal(SIGINT, signalHendler);
    count++;
    write(1, message, sizeof(message) - 1);
    errno = saveErrno;
}

int main()
{
    signal(SIGINT, signalHendler);

    while(count<TIMES)
        usleep(SLEEP);

    return 0;
}