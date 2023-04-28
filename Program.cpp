#include "headers/debug.hpp"
#include "headers/settings.hpp"
#include "headers/board.hpp"

#include <iostream>

int main(){

    test;

    settings &settings_instance = settings::get_instance();
    settings_instance.set_difficulty(difficulty::EASY);

    board &board_instance = board::get_instance();

    for(uint16_t i = 0; i < settings_instance.get_height(); ++i)
        for(uint16_t j = 0; j < settings_instance.get_width(); ++j)
            board_instance.review_cell({i, j});

    std::cout << board_instance << '\n';

    leaks;

}