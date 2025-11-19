#include <iostream>
#include <cmath>
#include <memory>

#include "GameBoard.h"


int main ()
{
    int num_cells;

    std::cout << "Select grid size" << std::endl;
    std::cin >> num_cells; // TODO Implement input validation. Except only integers that are perfect squares
    std::shared_ptr<GameBoard> game_board = std::make_shared<GameBoard>(num_cells);
    game_board->initGameBoard();
    game_board->printGameBoard();

    return 0;
}
