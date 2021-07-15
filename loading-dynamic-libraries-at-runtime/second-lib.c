#include"second-lib.h"

int avr(int a, int b, int c)
{
    return (a + b + c) / 3;
}

int maxi(int a, int b, int c)
{
    if(a>b)
    {
        return a>c ? a : c;
    }
    else
    {
        return b>c ? b : c;
    } 
}