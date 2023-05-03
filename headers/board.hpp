#pragma once

#include "settings.hpp"
#include <ostream>
#include <vector>

#define BOMB '@'
#define FLAG '$'
#define EMPTY '0'
#define UNCOVERED '#'

class board{

public:
    struct coords{ uint16_t x = 0, y = 0; };

public:
    ~board() = default;

    board(board const &) = delete;
    board(board &&) = delete;

    board &operator =(board const &) = delete;
    board &operator =(board &&) = delete;

    static board &get_instance();

    char get_cell(coords const) const;
    void flag_cell(coords const);
    void review_cell(coords const);

    void reset();

public:
    friend std::ostream &operator <<(std::ostream &, board const &);

private:
    board();

    void populate_bombs();

    bool cell_is_inside(coords const) const;
    bool is_bomb(coords const) const;

private:
    std::vector<std::vector<u_char>> _cells;
    uint16_t _bombs[30] = { 0, };

};

#ifdef DEBUG

TEST_CASE("Testing singleton property"){

    CHECK_EQ(&board::get_instance(), &board::get_instance());

}

#endif