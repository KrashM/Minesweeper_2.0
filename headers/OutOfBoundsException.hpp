#pragma once

#include <exception>

using std::exception;

class OutOfBoundsException: public exception{

    public: const char *what() const throw(){ return "Coordinates out of range"; }

}out_of_bounds;