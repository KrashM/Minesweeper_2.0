#include <random>
#include <iomanip>
#include "../headers/board.hpp"
#include "../headers/out_of_bounds.hpp"

using std::setw;

board &board::get_instance(){

    static board instance;
    return instance;

}

void board::review_cell(coords const c){

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

}

ostream &operator <<(ostream &os, board const &obj){

    os << "  ";
    for(uint16_t i = 0; i < settings::get_instance().get_width(); i++)
        os << ' ' << setw(2) << i + 1;
    os << '\n';

    for(uint16_t i = 0; i < settings::get_instance().get_height(); i++){

        os << setw(2) << i + 1;
        for(uint16_t j = 0; j < settings::get_instance().get_width(); j++)
            os << setw(2) << ' ' << obj._cells[i][j];
        os << '\n';

    }

    return os;

}

board::board(): _cells(new u_char *[settings::get_instance().get_height()]){
    
    for(uint16_t i = 0; i < settings::get_instance().get_height(); ++i){
        
        _cells[i] = new u_char[settings::get_instance().get_width()];

        for(uint16_t j = 0; j < settings::get_instance().get_width(); ++j)
            _cells[i][j] = UNCOVERED;

    }

    populate_bombs();

}

board::~board(){

    for(uint16_t i = 0; i < settings::get_instance().get_height(); i++)
        delete[] _cells[i];
    delete[] _cells;

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
    return c.x < settings::get_instance().get_height() && c.y < settings::get_instance().get_width();
}

bool board::is_bomb(coords const c) const{
    return _bombs[c.x] & 1 << c.y;
}