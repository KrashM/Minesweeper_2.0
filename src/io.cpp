#include "../headers/io.hpp"

io &io::get_instance(){

    static io instance;
    return instance;

}

void io::menu(){

    set_console();
    centering_string("Hello, player!");
    centering_string("Start Game");
    centering_string("Quit!");

}

void io::set_console(){

    uint16_t const width = 400, height = 400;
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);

}

void io::centering_string(std::string const &str){

	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    const size_t width = csbi.srWindow.Right - csbi.srWindow.Left;
    for(size_t i = 0; i < (width - str.length()) / 2; i++) std::cout << ' ';
    std::cout << str << '\n';

}