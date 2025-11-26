#include "../inc/Menus.h"
#include "InputHandlers.h"

#include <iostream>


// Choose the size of the game board grid
// Returns:
// TRUE if a grid size is chosen.
// FALSE if user chooses GO BACK option.
bool Menus::gridSizeMenu(std::shared_ptr<GameBoard>& game_board)
{
    std::cout << "--- NEW GAME ---" << std::endl;
    std::cout << "Please select grid size:" << std::endl;
    std::cout << "1. 3*3" << std::endl;
    std::cout << "2. 6*6" << std::endl;
    std::cout << "3. 9*9" << std::endl;
    std::cout << "0. GO BACK" << std::endl;
    switch (InputHandlers::getIntInRange(0, 3))
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
        return false;
    default:
        break;
    }
    return true;
}

// Guess/reveal cell
void Menus::guess(const std::shared_ptr<GameBoard>& game_board)
{
    game_board->revealCell();
}

// Flag cell
void Menus::flag(const std::shared_ptr<GameBoard>& game_board)
{
    game_board->flagCell();
}

// Save current game progress
void Menus::saveGame(const std::shared_ptr<GameBoard>& game_board)
{
    game_board->saveGame();
}

// Present user choices each turn.
void Menus::turn(const std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<bool>& run)
{
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Flag" << std::endl;
    std::cout << "2. Guess" << std::endl;
    std::cout << "3. Save game" << std::endl;
    std::cout << "0. Quit" << std::endl;
    switch (InputHandlers::getIntInRange(0, 3))
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

// Checks game status.
// If ACTIVE: new turn.
// If LOSS or WIN: end game.
void Menus::gameLoop(const std::shared_ptr<GameBoard>& game_board)
{
    std::shared_ptr<bool> run = std::make_shared<bool>(true);
    while (*run)
    {
        switch (game_board.get()->getGameStatus())
        {
        case GameBoard::GameStatus::ACTIVE:
            game_board->printGameBoard();
            turn(game_board, run);
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
void Menus::loadGame()
{
    std::shared_ptr<GameBoard> game_board;
    if (GameBoard::loadGame(game_board))
    {
    gameLoop(game_board);
    }
}

// Start a new game.
void Menus::newGame()
{
    std::shared_ptr<GameBoard> game_board;
    if (gridSizeMenu(game_board))
    {
    gameLoop(game_board);
    }
}

void Menus::mainMenu(const std::shared_ptr<bool>& run_game)
{
    while (*run_game)
    {
        std::cout << "--- MAIN MENU ---" << std::endl;
        std::cout << "1. START NEW GAME" << std::endl;
        std::cout << "2. LOAD GAME" << std::endl;
        std::cout << "0. QUIT" << std::endl;
        switch (InputHandlers::getIntInRange(0, 2))
        {
        case 1:
            Menus::newGame();
            break;
        case 2:
            Menus::loadGame();
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

