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
    sf::RectangleShape cell_shape(sf::Vector2f(settings::_cell_size - 1, settings::_cell_size - 1));

    for(uint16_t i = 0; i < setup.get_width(); ++i)
        for(uint16_t j = 0; j < setup.get_height(); ++j){

            cell_shape.setPosition(settings::_cell_size * i, settings::_cell_size * j);

            if(cells.get_cell({i, j}) == UNCOVERED) cell_shape.setFillColor(sf::Color(255, 255, 255));
            else if(cells.get_cell({i, j}) == BOMB) cell_shape.setFillColor(sf::Color::Red);
            else cell_shape.setFillColor(sf::Color(125, 125, 125));

            _window.draw(cell_shape);

        }

}

io::io(){

    settings &setup = settings::get_instance();
    setup.set_difficulty(difficulty::HARD);

    _window.create(sf::VideoMode(settings::get_instance().get_width() * settings::_cell_size, settings::get_instance().get_height() * settings::_cell_size), "Minesweeper", sf::Style::Close);

    bool pressed = false;

    std::chrono::time_point<std::chrono::steady_clock> previous_time = std::chrono::steady_clock::now();
    uint64_t lag = 0;
    uint16_t x = 0, y = 0;

    while(_window.isOpen()){

		uint64_t delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		lag += delta_time;

		previous_time += std::chrono::microseconds(delta_time);

        while(settings::_frame_duration <= lag){

            lag -= settings::_frame_duration;

            sf::Event event;
            while(_window.pollEvent(event))
                if(event.type == sf::Event::Closed)
                    _window.close();
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !pressed){

                pressed = !pressed;
                sf::Vector2i position = sf::Mouse::getPosition(_window);
                std::cout << position.x << ' ' << position.y << '\n';

            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){

                pressed = !pressed;
                board::get_instance().review_cell({x, y});
                ++x;
                y += x == settings::get_instance().get_width();
                y = y == settings::get_instance().get_height() ? 0 : y;
                x %= settings::get_instance().get_width();

            }

            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right && pressed)
                pressed = !pressed;

            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A && pressed)
                pressed = !pressed;
            
            if(lag < settings::_frame_duration){

                _window.clear();
                frame_update();
                _window.display();

            }
            
        }

    }

}