#include <iostream>
#include "headers/Board.hpp"
#include "headers/IO.hpp"

#include <string>
using std::cout;

int main(){

    system("cls");
    IO::menu();
    IO::centeringString("Hello there");
    // Board myBoard(Settings::EXPERT_22x22);
    // try{ myBoard.reviewCell(0, 2); }
    // catch(const std::exception& e){ std::cerr << e.what() << '\n'; }
    // cout << myBoard;

}