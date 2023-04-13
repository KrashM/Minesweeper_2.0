#include "../headers/settings.hpp"

settings &settings::get_instance(){

    static settings instance;
    return instance;

}

void settings::set_difficulty(difficulty const diff){

    switch(diff){

        case difficulty::EASY:
            _height = _width = 9;
            _bombs = 10;
            break;

        case difficulty::MEDIUM:
            _height = _width = 16;
            _bombs = 40;
            break;

        case difficulty::HARD:
            _height = 16;
            _width = 30;
            _bombs = 99;
            break;
        
        default:
            break;

    }

}

uint16_t const settings::get_height() const{ return _height; }
uint16_t const settings::get_width() const{ return _width; }
uint16_t const settings::get_bombs() const{ return _bombs; }