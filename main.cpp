#include <iostream>
#include <cmath>
#include <memory>

#include "GameBoard.h"


int main ()
{
    int num_cells;
    std::shared_ptr<bool> running = std::make_shared<bool>(true);
    std::cout << "RUNNING : " << *running << std::endl;

    std::cout << "Select grid size" << std::endl;
    std::cin >> num_cells; // TODO Implement input validation. Except only integers that are perfect squares
    std::shared_ptr<GameBoard> game_board = std::make_shared<GameBoard>(num_cells);
    game_board->initGameBoard();
    game_board->printGameBoard();

    char chars[] = "C3";
    while (*running)
    {
        std::cout << "ENTER : " << std::endl;

        std::cin >> chars;
     // game_board->findCell(chars);
    game_board->userChoice(chars, 1, running);
        game_board->printGameBoard();
    // std::cout << "RUNNING : " << *running << std::endl;
    }


    return 0;
}
