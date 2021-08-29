/*
    This simple program demonstrates making STDIN non blocking
    This code is analogous to one example from the course
    Системное программирование by Технострим Mail.Ru Group
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

void makeNonblocking(int fd)
{
    int oldFlags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, oldFlags | O_NONBLOCK);
}

int main()
{
    makeNonblocking(STDIN_FILENO);
    int value = 0;
    int rc = scanf("%d", &value);
    printf("scanf rc = %d\n", rc);
    printf("scanf error = %s\n", strerror(errno));
    rc = read(STDIN_FILENO, &value, sizeof(value));
    printf("read rc = %d\n", rc);
    printf("read error = %s\n", strerror(errno));

    while(1)
    {
        rc = scanf("%d", &value);
        if(rc > 0 || (errno != EAGAIN && errno != EWOULDBLOCK))
            break;
    }
    printf("value = %d\n", value);

    return 0;
}