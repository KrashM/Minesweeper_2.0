#define DEBUG
// #define DEBUG_NEW
#include "headers/settings.hpp"

#include <iostream>

#ifdef DEBUG
#define test doctest::Context().run()
#else
#define test
#endif

using std::cout;

int main(){

    test;

    checkMemoryLeaks();

}