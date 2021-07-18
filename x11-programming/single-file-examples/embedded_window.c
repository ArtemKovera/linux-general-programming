/*

    This program is analogous to the one from ShellWave youtube channel:
    https://www.youtube.com/watch?v=kou3swzR554

*/
#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/Xos.h>
#include<X11/Xatom.h>
#include<stdbool.h>

int main()
{
    Display *dpy;
    int screen;
    Window win;
    Window embeddedWindow;
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


    embeddedWindow = XCreateSimpleWindow(dpy, win, 20, 20, 200, 100, 2, BlackPixel(dpy, screen), WhitePixel(dpy, screen));

    XSelectInput(dpy, embeddedWindow, ExposureMask | KeyPressMask);
    XMapWindow(dpy, embeddedWindow);

    while(true)
    {
        XNextEvent(dpy, &evn);
    }

    return 0;
}