#pragma once

#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>

class io{

public:
    static io &get_instance();

public:
    io(io const &) = delete;
    io(io &&) = delete;

    io &operator =(io const &) = delete;
    io &operator =(io &&) = delete;

    void menu();
    void set_console();
    void centering_string(std::string const &);

private:
    io() = default;

};