#include "../headers/cell.hpp"

cell::cell(): _value(UNCOVERED){}
cell::cell(const u_char value): _value(value){}

u_char cell::get_value() const{ return this -> _value; }
void cell::set_value(u_char const value){ this -> _value = value; }