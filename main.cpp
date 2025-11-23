#include <iostream>
#include <memory>

#include "GameBoard.h"
#include "utils/inc/InputHandlers.h"

void gridSizeMenu(std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<bool>& runGame)
{
    std::cout << "--- NEW GAME ---" << std::endl;
    std::cout << "Please select grid size:" << std::endl;
    std::cout << "1. 3*3" << std::endl;
    std::cout << "2. 6*6" << std::endl;
    std::cout << "3. 9*9" << std::endl;
    std::cout << "0. QUIT" << std::endl;
    switch (getIntInRange(0, 3))
    {
    case 1:
        GameBoard::initGameBoard(game_board, 9);
        break;
    case 2:
        GameBoard::initGameBoard(game_board, 36);
        break;
    case 3:
        GameBoard::initGameBoard(game_board, 81);
        break;
    case 0:
        *runGame = false;
        break;
    default:
        break;
    }
}

void userChoice(const std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<GameBoard::GameStatus>& game_status)
{
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. Flag" << std::endl;
        std::cout << "2. Guess" << std::endl;
        const int choice = getIntInRange(1, 2);
        const std::string coord = getValidCoordinate(game_board.get()->getRows(), game_board.get()->getColumns());
        const int cell = game_board->findCell(coord.c_str());
        const std::vector<std::shared_ptr<Cell>> cells = game_board->getCells();
        game_board->getAdjacentMines(cell);
        switch (choice)
        {
        case 1:
            std::cout << "from flag" << std::endl;

            game_board->flagCell(cell);
            break;
        case 2:
            std::cout << "from reveal" << std::endl;

            game_board->revealCell(cell);
            break;
        default:
            break;
        }
        *game_status = game_board->checkGameStatus(cell);
}

void gameMenu(std::shared_ptr<GameBoard>& game_board)
{
    std::shared_ptr<bool> run = std::make_shared<bool>(true);
    std::shared_ptr<GameBoard::GameStatus> status = std::make_shared<GameBoard::GameStatus>(GameBoard::GameStatus::ACTIVE);
    gridSizeMenu(game_board, run);
    while (*run)
    {
        switch (*status)
        {
        case GameBoard::GameStatus::ACTIVE:
            game_board->printGameBoard();
            userChoice(game_board, run, status);
            break;
        case GameBoard::GameStatus::WIN:
            std::cout << "YOU HAVE WON!" << std::endl;
            // TODO Add wins to player?
            *run = false;
            break;
        case GameBoard::GameStatus::LOSS:
            std::cout << "YOU HAVE LOST!" << std::endl;
            // TODO Add loss to player?
            *run = false;
            break;
        }
    }
}

void mainMenu(std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<bool>& runGame)
{
        while (*runGame)
        {
            std::cout << "--- MAIN MENU ---" << std::endl;
                std::cout << "1. START NEW GAME" << std::endl;
                std::cout << "0. QUIT" << std::endl;
                const int choice = getIntInRange(0, 1);
                switch (choice)
                {
                case 1:
                    gameMenu(game_board);
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
    while (*runGame)
    {
        mainMenu(game_board, runGame);
    }
    return 0;
}
