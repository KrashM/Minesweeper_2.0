#include <random>
#include <iomanip>
#include "../headers/board.hpp"
#include "../headers/out_of_bounds.hpp"

board &board::get_instance(){

    static board instance;
    return instance;

}

char board::get_cell(coords const c) const{
    if(!cell_is_inside(c)) throw out_of_bounds();
    return _cells[c.x][c.y];
}

void board::flag_cell(coords const c){
    if(!cell_is_inside(c)) throw out_of_bounds();
    _cells[c.x][c.y] = _cells[c.x][c.y] == UNCOVERED ? FLAG : UNCOVERED;
}

void board::review_cell(coords const c){

    if(!cell_is_inside(c)) throw out_of_bounds();

    if(_cells[c.x][c.y] != UNCOVERED) return;

    if(is_bomb(c)){

        _cells[c.x][c.y] = BOMB;
        return;

    }

    coords neighbours[8] = {

        {uint16_t(c.x - 1), uint16_t(c.y - 1)},
        {uint16_t(c.x - 1), uint16_t(c.y)},
        {uint16_t(c.x - 1), uint16_t(c.y + 1)},
        {uint16_t(c.x), uint16_t(c.y + 1)},
        {uint16_t(c.x + 1), uint16_t(c.y + 1)},
        {uint16_t(c.x + 1), uint16_t(c.y)},
        {uint16_t(c.x + 1), uint16_t(c.y - 1)},
        {uint16_t(c.x), uint16_t(c.y - 1)}

    };

    _cells[c.x][c.y] = EMPTY;

    for(uint16_t i = 0; i < 8; ++i)
        if(cell_is_inside(neighbours[i]))
            _cells[c.x][c.y] += is_bomb(neighbours[i]);
    
    if(_cells[c.x][c.y] == EMPTY)
        for(uint16_t i = 0; i < 8; ++i)
            if(cell_is_inside(neighbours[i]))
                review_cell(neighbours[i]);

}

void board::reset(){

    _cells.resize(settings::get_instance().get_width(), std::vector<u_char>(settings::get_instance().get_height(), UNCOVERED));
    populate_bombs();

}

std::ostream &operator <<(std::ostream &os, board const &obj){

    os << "  ";
    for(uint16_t i = 0; i < settings::get_instance().get_width(); i++)
        os << ' ' << std::setw(2) << i + 1;
    os << '\n';

    for(uint16_t i = 0; i < settings::get_instance().get_height(); i++){

        os << std::setw(2) << i + 1;
        for(uint16_t j = 0; j < settings::get_instance().get_width(); j++)
            os << std::setw(2) << ' ' << obj._cells[j][i];
        os << '\n';

    }

    return os;

}

board::board(){
    reset();
}

void board::populate_bombs(){

    coords c;

    srand(time(nullptr));

    for(uint16_t i = 0; i < settings::get_instance().get_bombs(); i++){

        do{

            c.x = rand() % settings::get_instance().get_width();
            c.y = rand() % settings::get_instance().get_height();

        }while(is_bomb(c));

        _bombs[c.x] |= 1 << c.y;

    }

}

bool board::cell_is_inside(coords const c) const{
    return c.x < settings::get_instance().get_width() && c.y < settings::get_instance().get_height();
}

bool board::is_bomb(coords const c) const{
    return _bombs[c.x] & 1 << c.y;
}