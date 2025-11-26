#ifndef MENUS_H
#define MENUS_H

#include <memory>

#include "GameBoard.h"


class Menus
{

public:
    static void mainMenu(const std::shared_ptr<bool>& run_game);

private:
    static void newGame();
    static void loadGame();
    static void gameLoop(const std::shared_ptr<GameBoard>& game_board);
    static void turn(const std::shared_ptr<GameBoard>& game_board, const std::shared_ptr<bool>& run);
    static void saveGame(const std::shared_ptr<GameBoard>& game_board);
    static void flag(const std::shared_ptr<GameBoard>& game_board);
    static void guess(const std::shared_ptr<GameBoard>& game_board);
    static bool gridSizeMenu(std::shared_ptr<GameBoard>& game_board);

};


#endif