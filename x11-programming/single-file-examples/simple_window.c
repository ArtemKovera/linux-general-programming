/*

    This program is analogous to the one from ShellWave youtube channel:
    https://www.youtube.com/watch?v=NWYwDXN7b_s&list=PLypxmOPCOkHV4cwikC5_7Z981_EBfErS1

*/
#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<stdbool.h>

int main()
{
    Display *dpy;
    int screen;
    Window win;
    XEvent evn;

    dpy = XOpenDisplay(NULL);

    if(dpy == NULL)
    {
        fprintf(stderr, "open display failure\n");
        exit(EXIT_FAILURE);
    }

    screen = DefaultScreen(dpy);

    win = XCreateSimpleWindow(dpy, RootWindow(dpy, screen), 300, 300, 500, 300, 1, BlackPixel(dpy, screen), WhitePixel(dpy, screen));

    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);

    while(true)
    {
        XNextEvent(dpy, &evn);
    }

    return 0;
}