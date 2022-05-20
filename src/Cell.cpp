#include "../headers/Cell.hpp"

Cell::Cell(): _value('0'){}
Cell::Cell(const u_char value): _value(value){}
Cell::Cell(const Cell &other){ this -> copy(other); }
Cell &Cell::operator =(const Cell &other){
    
    if(this != &other) this -> copy(other);
    return *this;
    
}
Cell &Cell::operator ++(){

    this -> _value++;
    return *this;

}

Cell Cell::operator ++(int){

    Cell old = *this;
    ++*this;
    return old;

}

u_char Cell::getValue() const{ return this -> _value; }
void Cell::copy(const Cell &other){ this -> _value = other._value; }