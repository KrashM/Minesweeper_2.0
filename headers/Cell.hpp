#pragma once

#include "Types.hpp"

class Cell{

    public:
        Cell();
        Cell(const u_char);
        Cell(const Cell &);

        Cell &operator =(const Cell &);
        Cell &operator ++();
        Cell operator ++(int);

        u_char getValue() const;

    private:
        u_char _value;

        void copy(const Cell &);

};