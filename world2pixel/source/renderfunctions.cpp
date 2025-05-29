#include "mainheader.h"

void cchange(int c) //Funkcja zmiany koloru tekstu!
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

void renderpixel(int asciicode, int color, int valuetocheck = 1, int vtcgreaterthan = 0, int vtcsmallerthan = 2)
{
    if(valuetocheck > vtcgreaterthan && valuetocheck < vtcsmallerthan)
    {
        cchange(color);
        std::cout<<char(asciicode);
    }
}