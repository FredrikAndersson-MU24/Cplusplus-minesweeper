#include "GameBoard.h"
#include "utils/inc/InputHandlers.h"

#include <iostream>
#include <memory>

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

void guess(const std::shared_ptr<GameBoard>& game_board)
{
    game_board->revealCell();
}


void flag(const std::shared_ptr<GameBoard>& game_board)
{

    game_board->flagCell();
}

// Save current game progress
void saveGame(const std::shared_ptr<GameBoard>& game_board)
{
    game_board->saveGame();
}

// Present user choices each turn.
void turn(const std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<bool>& run)
{
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Flag" << std::endl;
    std::cout << "2. Guess" << std::endl;
    std::cout << "3. Save game" << std::endl;
    std::cout << "0. Quit" << std::endl;
    switch (getIntInRange(0, 3))
    {
    case 1:
        flag(game_board);
        break;
    case 2:
        guess(game_board);
        break;
    case 3:
        saveGame(game_board);
        break;
    case 0:
        *run = false;
        break;
    default:
        break;
    }
}

void gameMenu()
{
    std::shared_ptr<GameBoard> game_board;
    std::shared_ptr<bool> run = std::make_shared<bool>(true);
    gridSizeMenu(game_board, run);
    while (*run)
    {
        switch (game_board.get()->getGameStatus())
        {
        case GameBoard::GameStatus::ACTIVE:
            game_board->printGameBoard();
            takeTurn(game_board, run);
            break;
        case GameBoard::GameStatus::WIN:
            game_board->endGame("YOU WON!");
            *run = false;
            break;
        case GameBoard::GameStatus::LOSS:
            game_board->endGame("YOU LOST!");
            *run = false;
            break;
        }
    }
}

// Load game from file.
void loadGame()
{
    std::shared_ptr<GameBoard> game_board;
    if (GameBoard::loadGame(game_board))
    {
    gameLoop(game_board);
    }
}

// Start a new game.
void newGame()
{
    std::shared_ptr<GameBoard> game_board;
    if (gridSizeMenu(game_board))
    {
    gameLoop(game_board);
    }
}

void mainMenu(const std::shared_ptr<bool>& run_game)
{
    while (*run_game)
    {
        std::cout << "--- MAIN MENU ---" << std::endl;
        std::cout << "1. START NEW GAME" << std::endl;
        std::cout << "2. LOAD GAME" << std::endl;
        std::cout << "0. QUIT" << std::endl;
        switch (getIntInRange(0, 2))
        {
        case 1:
            newGame();
            break;
        case 2:
            loadGame();
            break;
        case 0:
            *run_game = false;
            break;
        default:
            std::cout << "PLEASE ENTER A VALID CHOICE!" << std::endl;
            break;
        }
    }
}


int main ()
{
    const std::shared_ptr<bool> runGame = std::make_shared<bool>(true);
    while (*runGame)
    {
        mainMenu(runGame);
    }
    return 0;
}
