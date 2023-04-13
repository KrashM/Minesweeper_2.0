#pragma once

#include "Cell.hpp"
#include "Settings.hpp"
#include <ostream>

using std::ostream;

class Board{

    public:
        Board();
        Board(const Settings &);
        Board(const Board &);
        ~Board();

        Board &operator =(const Board &);
        friend ostream &operator <<(ostream &, const Board &);

        void populateBombs();
        void calculateCells();
        void checkNeighbourCells(const u_short, const u_short);
        bool cellIsInside(const u_short, const u_short) const;
        unsigned char getCell(const u_short, const u_short) const;
        unsigned char reviewCell(const u_short, const u_short) const;

    private:
        Cell **_cells;
        bool **_reviewed;
        u_short _width, _height, _nMines;

        void del();
        void copy(const Board &);

};