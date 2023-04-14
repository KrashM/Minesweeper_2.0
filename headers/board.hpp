#pragma once

#include "settings.hpp"
#include <ostream>

#define BOMB '@'
#define FLAG '$'
#define EMPTY '0'
#define UNCOVERED '#'

using std::ostream;

class board{

    public:
        struct coords{
            uint16_t x, y;
        };

        ~board();

        board(board const &) = delete;
        board(board &&) = delete;

        board &operator =(board const &) = delete;
        board &operator =(board &&) = delete;

        static board &get_instance();

        void review_cell(coords const);
        u_char get_cell(coords const) const;

        friend ostream &operator <<(ostream &, board const &);

    private:
        board();

        void populate_bombs();

        bool cell_is_inside(coords const) const;
        bool is_bomb(coords const) const;

        u_char **_cells;
        uint16_t _bombs[30];

};