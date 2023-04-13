#pragma once

#include "settings.hpp"

#define BOMB '@'
#define FLAG '$'
#define EMPTY ' '
#define UNCOVERED '#'

class cell{

    public:
        cell();
        cell(u_char const);

        u_char get_value() const;
        void set_value(u_char const);

    private:
        u_char _value;

};