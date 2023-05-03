#include "../headers/io.hpp"
#include "../headers/board.hpp"
#include "../headers/settings.hpp"
#include <chrono>

io &io::get_instance(){

    static io instance;
    return instance;

}

#include <iostream>

void io::frame_update(){

    settings &setup = settings::get_instance();
    board &cells = board::get_instance();
    sf::RectangleShape cell_shape(sf::Vector2f((settings::_cell_size - 1) * settings::_scale, (settings::_cell_size - 1) * settings::_scale));

    sf::Sprite sprite;
    sf::Texture sprite_texture;

    sprite_texture.loadFromFile("../resources/images/minesweeper-sprites.png");
    sprite.setTexture(sprite_texture);
    sprite.scale({settings::_scale, settings::_scale});

    for(uint16_t i = 0; i < setup.get_width(); ++i)
        for(uint16_t j = 0; j < setup.get_height(); ++j){

            cell_shape.setPosition(settings::_cell_size * i * settings::_scale, settings::_cell_size * j * settings::_scale);
            cell_shape.setFillColor(sf::Color(255, 255, 255));
            _window.draw(cell_shape);

            sprite.setPosition(settings::_cell_size * i * settings::_scale, settings::_cell_size * j * settings::_scale);

            u_char cell = cells.get_cell({i, j});

            if(cell == UNCOVERED)
                sprite.setTextureRect(sf::IntRect(0, 51, settings::_cell_size - 1, settings::_cell_size - 1));
            else if(cell == EMPTY)
                sprite.setTextureRect(sf::IntRect(17, 51, settings::_cell_size - 1, settings::_cell_size - 1));
            else if(cell == BOMB)
                sprite.setTextureRect(sf::IntRect(102, 51, settings::_cell_size - 1, settings::_cell_size - 1));
            else if(cell == FLAG)
                sprite.setTextureRect(sf::IntRect(34, 51, settings::_cell_size - 1, settings::_cell_size - 1));
            else if(cell > EMPTY && cell < EMPTY + 9)
                sprite.setTextureRect(sf::IntRect((cell - 1 - EMPTY) * (settings::_cell_size + 1), 68, settings::_cell_size - 1, settings::_cell_size - 1));

            _window.draw(sprite);

        }

}

void io::game_loop(){

    bool pressed = false, running = true;

    std::chrono::time_point<std::chrono::steady_clock> previous_time = std::chrono::steady_clock::now();
    uint64_t lag = 0;
    uint16_t x = 0, y = 0;

    board::get_instance().reset();

    while(running){

		uint64_t delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		lag += delta_time;

		previous_time += std::chrono::microseconds(delta_time);

        while(settings::_frame_duration <= lag){

            lag -= settings::_frame_duration;

            sf::Event event;
            while(_window.pollEvent(event))
                if(event.type == sf::Event::Closed)
                    _window.close();
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !pressed){

                pressed = !pressed;
                sf::Vector2i coordinates = sf::Mouse::getPosition(_window);
                coordinates.x /= settings::_cell_size * settings::_scale;
                coordinates.y /= settings::_cell_size * settings::_scale;

                board::coords position = {(uint16_t)coordinates.x, (uint16_t)coordinates.y};

                if(board::get_instance().get_cell(position) == UNCOVERED)
                    board::get_instance().review_cell(position);

                if(board::get_instance().get_cell(position) == BOMB){

                    std::cout << "Game Over!\n";
                    running = false;
                    break;

                }

            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !pressed){

                pressed = !pressed;
                sf::Vector2i coordinates = sf::Mouse::getPosition(_window);
                coordinates.x /= settings::_cell_size * settings::_scale;
                coordinates.y /= settings::_cell_size * settings::_scale;

                board::coords position = {(uint16_t)coordinates.x, (uint16_t)coordinates.y};

                board::get_instance().flag_cell(position);

            }

            if(event.type == sf::Event::MouseButtonReleased && pressed)
                pressed = !pressed;

            if(lag < settings::_frame_duration){

                _window.clear();
                frame_update();
                _window.display();

            }
            
        }

    }

}

void io::menu(){

    while(_window.isOpen()){

        sf::Event event;
        while(_window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                _window.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) game_loop();

    }

}

io::io(){

    settings &setup = settings::get_instance();
    setup.set_difficulty(difficulty::HARD);

    _window.create(sf::VideoMode(settings::get_instance().get_width() * settings::_cell_size * settings::_scale, settings::get_instance().get_height() * settings::_cell_size * settings::_scale), "Minesweeper", sf::Style::Close);

}