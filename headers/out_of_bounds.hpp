#pragma once

#include <exception>

class out_of_bounds: public std::exception{

    public:
        char const *what() const throw(){
            return "Coordinates out of range";
        }

};