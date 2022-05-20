#include <iostream>
#include "headers/Board.hpp"

using std::cout;

int main(){

    system("cls");
    Board myBoard(Settings::EXPERT_22x22);
    try{ myBoard.reviewCell(0, 2); }
    catch(const std::exception& e){ std::cerr << e.what() << '\n'; }
    cout << myBoard;

}