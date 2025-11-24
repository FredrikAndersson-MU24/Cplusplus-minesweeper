#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <memory>
#include <vector>

#include "Cell.h"


class GameBoard
{
public:
    explicit GameBoard(int num_cells);
    ~GameBoard() = default;
    void printGameBoard() const;
    static void initGameBoard(std::shared_ptr<GameBoard>& game_board, int size);
    int findCell(const char* coord);
    void flagCell();
    void revealCell();
    void revealAllMines() const;
    void endGame(const std::string& prompt) const;
    enum class GameStatus {ACTIVE, WIN, LOSS};
    [[nodiscard]] GameStatus getGameStatus() const;
    void updateGameStatus();
    std::vector<int> getColumns();
    std::vector<char> getRows();

private:
    int num_cells; // Total number of cells.
    std::vector<int> columns;
    std::vector<char> rows;
    std::vector<std::shared_ptr<Cell>> cells;
    int grid_size; // Sqrt of num_cells. To set num of rows and columns.
    int num_mines;
    int revealed_cells; // Number of cells that the player has revealed. Used for determining WIN state.
    enum class Placement {LEFT, RIGHT, TOP, BOTTOM, TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT, CENTER};
    Placement placement{};
    GameStatus game_status;

    void initColumns();
    void initRows();
    void initCells();
    void randomizeMines() const;
    void setPlacement(int row_index, int col_index);
    void getAdjacentMines(int cell);
    [[nodiscard]] bool hasAdjacentMineAtMinusGridSizeMinusOne(int cell) const;
    [[nodiscard]] bool hasAdjacentMineAtMinusGridSize(int cell) const;
    [[nodiscard]] bool hasAdjacentMineAtMinusGridSizePlusOne(int cell) const;
    [[nodiscard]] bool hasAdjacentMineAtMinusOne(int cell) const;
    [[nodiscard]] bool hasAdjacentMineAtPlusOne(int cell) const;
    [[nodiscard]] bool hasAdjacentMineAtPlusGridSizeMinusOne(int cell) const;
    [[nodiscard]] bool hasAdjacentMineAtPlusGridSize(int cell) const;
    [[nodiscard]] bool hasAdjacentMineAtPlusGridSizePlusOne(int cell) const;
    [[nodiscard]] int getAdjacentMinesTopLeft(int cell) const;
    [[nodiscard]] int getAdjacentMinesLeft(int cell) const;
    [[nodiscard]] int getAdjacentMinesRight(int cell) const;
    [[nodiscard]] int getAdjacentMinesTopRight(int cell) const;
    [[nodiscard]] int getAdjacentMinesBottomRight(int cell) const;
    [[nodiscard]] int getAdjacentMinesBottomLeft(int cell) const;
    [[nodiscard]] int getAdjacentMinesTop(int cell) const;
    [[nodiscard]] int getAdjacentMinesBottom(int cell) const;
    [[nodiscard]] int getAdjacentMinesCenter(int cell) const;
};


#endif