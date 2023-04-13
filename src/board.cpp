#include "../headers/Board.hpp"
#include "../headers/OutOfBoundsException.hpp"
#include <random>
#include <iomanip>

using std::setw;

Board::Board(): _cells(nullptr), _reviewed(nullptr){}
Board::Board(const Settings &settings): _width(settings.getWidth()), _height(settings.getHeight()), _nMines(settings.getBombs()), _cells(new Cell*[settings.getHeight()]), _reviewed(new bool*[settings.getHeight()]){
    
    for(u_short i = 0; i < settings.getHeight(); i++) this -> _cells[i] = new Cell[settings.getWidth()];
    for(u_short i = 0; i < settings.getHeight(); i++) this -> _reviewed[i] = new bool[settings.getWidth()];
    this -> populateBombs();
    this -> calculateCells();

}
Board::Board(const Board &other){ this -> copy(other); }
Board::~Board(){ this -> del(); }

Board &Board::operator =(const Board &other){

    if(this != &other){

        this -> del();
        this -> copy(other);

    }

    return *this;

}

void Board::populateBombs(){

    for(u_short i = 0; i < this -> _nMines; i++){

        u_short x, y;
        do{

            x = rand() % _width;
            y = rand() % _height;

        }while(this -> _cells[y][x].getValue() == -1);

        this -> _cells[y][x] = '*';

    }

}

void Board::calculateCells(){

    for(u_short i = 0; i < this -> _height; i++)
        for(u_short j = 0; j < this -> _width; j++)
            if(this -> _cells[i][j].getValue() != '*')
                this -> checkNeighbourCells(i, j);

}

void Board::checkNeighbourCells(const u_short i, const u_short j){

    if(this -> cellIsInside(i - 1, j - 1) && this -> _cells[i - 1][j - 1].getValue() == '*') this -> _cells[i][j]++;
    if(this -> cellIsInside(i - 1, j) && this -> _cells[i - 1][j].getValue() == '*') this -> _cells[i][j]++;
    if(this -> cellIsInside(i - 1, j + 1) && this -> _cells[i - 1][j + 1].getValue() == '*') this -> _cells[i][j]++;
    if(this -> cellIsInside(i, j - 1) && this -> _cells[i][j - 1].getValue() == '*') this -> _cells[i][j]++;
    if(this -> cellIsInside(i, j + 1) && this -> _cells[i][j + 1].getValue() == '*') this -> _cells[i][j]++;
    if(this -> cellIsInside(i + 1, j - 1) && this -> _cells[i + 1][j - 1].getValue() == '*') this -> _cells[i][j]++;
    if(this -> cellIsInside(i + 1, j) && this -> _cells[i + 1][j].getValue() == '*') this -> _cells[i][j]++;
    if(this -> cellIsInside(i + 1, j + 1) && this -> _cells[i + 1][j + 1].getValue() == '*') this -> _cells[i][j]++;

}

bool Board::cellIsInside(const u_short i, const u_short j) const{ return i >= 0 && i < this -> _height && j >= 0 && j < this -> _width; }
unsigned char Board::reviewCell(const u_short i, const u_short j) const{
    
    if(!this -> cellIsInside(i, j)) throw out_of_bounds;
    this -> _reviewed[i][j] = true;
    return this -> _cells[i][j].getValue();
    
}
unsigned char Board::getCell(const u_short i, const u_short j) const{
    
    if(!this -> cellIsInside(i, j)) throw out_of_bounds;
    return (this -> _reviewed[i][j]) ? this -> _cells[i][j].getValue() : '-';
    
}

void Board::del(){

    for(u_short i = 0; i < this -> _height; i++)
        delete[] this -> _cells[i];
    delete[] this -> _cells;

    for(u_short i = 0; i < this -> _height; i++)
        delete[] this -> _reviewed[i];
    delete[] this -> _reviewed;

}

void Board::copy(const Board &other){
    
    this -> _height = other._height;
    this -> _width = other._width;
    this -> _cells = new Cell*[other._height];
    for(u_short i = 0; i < other._height; i++){

        this -> _cells[i] = new Cell[other._width];
        for(u_short j = 0; j < other._width; j++)
            this -> _cells[i][j] = other._cells[i][j];

    }

    this -> _reviewed = new bool*[other._height];
    for(u_short i = 0; i < other._height; i++){

        this -> _reviewed[i] = new bool[other._width];
        for(u_short j = 0; j < other._width; j++)
            this -> _reviewed[i][j] = other._reviewed[i][j];

    }
    
}

ostream &operator <<(ostream &os, const Board &obj){

    os << "  ";
    for(u_short i = 0; i < obj._width; i++) os << ' ' << setw(2) << i;
    os << '\n';
    for(u_short i = 0; i < obj._height; i++){

        os << setw(2) << i;
        for(u_short j = 0; j < obj._width; j++) os << setw(2) << ' ' << obj.getCell(i, j);
        os << '\n';

    }
    return os;

}