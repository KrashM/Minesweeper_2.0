#pragma once

#include <SFML/Graphics.hpp>

class io{

public:
    static io &get_instance();

public:
    ~io() = default;

    io(io const &) = delete;
    io(io &&) = delete;

    io &operator =(io const &) = delete;
    io &operator =(io &&) = delete;

    void frame_update();
    void game_loop();
    void menu();

private:
    io();

private:
    sf::RenderWindow _window;

};