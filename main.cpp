#include <iostream>
#include <cmath>
#include <memory>

#include "GameBoard.h"


void gridSizeMenu(std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<bool>& runGame)
{
    int choice;
    std::cout << "--- NEW GAME ---" << std::endl;
    std::cout << "Please select grid size:" << std::endl;
    std::cout << "1. 3*3" << std::endl;
    std::cout << "2. 6*6" << std::endl;
    std::cout << "3. 9*9" << std::endl;
    std::cout << "0. QUIT" << std::endl;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        game_board = std::make_shared<GameBoard>(9);
        break;
    case 2:
        game_board = std::make_shared<GameBoard>(36);
        break;
    case 3:
        game_board = std::make_shared<GameBoard>(81);
        break;
    case 0:
        *runGame = false;
        break;
    default:
        break;
    }
}

void userChoice(const std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<bool>& runGame)
{
    int choice;
    bool run = true;
    while (run)
    {
        std::cout << "What would you like to do?" << std::endl;
        char chars[] = "A1";
        std::cout << "1. Flag" << std::endl;
        std::cout << "2. Guess" << std::endl;
        std::cin >> choice;
        std::cout << "Enter coordinate  : " << std::endl;
        std::cin >> chars;
        const int cell = game_board->findCell(chars);
        const std::vector<std::shared_ptr<Cell>> cells = game_board->getCells();
        game_board->getAdjacentMines(cell);
        switch (choice)
        {
        case 1:
            cells.at(cell).get()->setIsFlagged(true);
            break;
        case 2:
            cells.at(cell).get()->setIsGuessed(true);
            if (cells.at(cell).get()->getHasMine())
            {
                std::cout << "BA-DUM! YOU STEPPED ON A MINE" << std::endl;
                std::cout << "WOULD YOU LIKE TO PLAY AGAIN?" << std::endl;
                std::cout << "1. YES" << std::endl;
                std::cout << "2. NO" << std::endl;
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                    run = false;
                    break;
                case 2:
                    *runGame = false;
                    break;
                default:
                    break;
                }
            }
            break;
        default:
            break;
        }
        game_board->printGameBoard();
    }

}

void choiceMenu(const std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<bool>& running)
{

}

void mainMenu(std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<bool>& runGame)
{
        int choice;
        while (*runGame)
        {
            std::cout << "--- MAIN MENU ---" << std::endl;
                std::cout << "1. START NEW GAME" << std::endl;
                std::cout << "0. QUIT" << std::endl;
                std::cin >> choice;
                switch (choice)
                {
                case 1:
                    gridSizeMenu(game_board);
                    userChoice(game_board, runGame);
                    break;
                case 0:
                    *runGame = false;
                    break;
                default:
                    std::cout << "PLEASE ENTER A VALID CHOICE!" << std::endl;
                    break;
                }
        }
}


int main ()
{
    std::shared_ptr<GameBoard> game_board;
    const std::shared_ptr<bool> runGame = std::make_shared<bool>(true);
    std::cout << "RUNNING : " << *runGame << std::endl;




    while (*runGame)
    {
        mainMenu(game_board, runGame);
    }


    return 0;
}
