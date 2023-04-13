#pragma once

#include <iostream>
#include <iomanip>
#include <windows.h>

class IO{

    public:
        static void setConsole();
        static void menu();
        static void centeringString(const char *);

};