#include "../headers/IO.hpp"
#include "../headers/Types.hpp"

using std::cout;
using std::ios;
using std::setw;

void IO::centeringString(const char *s){

	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    const size_t width = csbi.srWindow.Right - csbi.srWindow.Left;
    for(size_t i = 0; i < (width - strlen(s)) / 2; i++) cout << ' ';
    cout << s << '\n';

}

void IO::setConsole(){

    const u_short width = 400, height = 400;
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);

}

void IO::menu(){

    IO::setConsole();
    IO::centeringString("Hello, player!");
    IO::centeringString("Start Game");
    IO::centeringString("Quit!");

}