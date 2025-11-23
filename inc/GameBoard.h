#ifndef INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H
#define INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H
#include <memory>
#include <vector>

#include "Cell.h"

class GameBoard
{
public:
    explicit GameBoard(int num_cells);
    ~GameBoard();
    void printGameBoard() const;
    void initGameBoard();
    int findCell(const char* coord);
    void getAdjacentMines(int cell);
    void flagCell(int cell);
    void revealCell(int cell);
    // int validateCell(const char* coord);
    std::vector<std::shared_ptr<Cell>> getCells();
    enum class GameStatus {ACTIVE, WIN, LOSS};
    GameStatus checkGameStatus(int cell);
    std::vector<int> getColumns();
    std::vector<char> getRows();

private:
    int num_cells; // Total number of cells.
    std::vector<int> columns;
    std::vector<char> rows;
    std::vector<std::shared_ptr<Cell>> cells;
    int grid_size; // Sqrt of num_cells. To set num of rows and columns.
    int num_mines;
    int revealed_cells;
    enum class Placement {LEFT, RIGHT, TOP, BOTTOM, TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT, CENTER};
    Placement placement{};
    GameStatus game_status{};
    void initColumns();
    void initRows();
    void initCells();
    void randomizeMines() const;
    void getPlacement(int row_index, int col_index);
    bool hasAdjacentMineAtMinusGridSizeMinusOne(int cell) const;
    bool hasAdjacentMineAtMinusGridSize(int cell) const;
    bool hasAdjacentMineAtMinusGridSizePlusOne(int cell) const;
    bool hasAdjacentMineAtMinusOne(int cell) const;
    bool hasAdjacentMineAtPlusOne(int cell) const;
    bool hasAdjacentMineAtPlusGridSizeMinusOne(int cell) const;
    bool hasAdjacentMineAtPlusGridSize(int cell) const;
    bool hasAdjacentMineAtPlusGridSizePlusOne(int cell);
    int getAdjacentMinesTopLeft(int cell);
    int getAdjacentMinesLeft(int cell);
    int getAdjacentMinesRight(int cell);
    int getAdjacentMinesTopRight(int cell);
    int getAdjacentMinesBottomRight(int cell);
    int getAdjacentMinesBottomLeft(int cell);
    int getAdjacentMinesTop(int cell);
    int getAdjacentMinesBottom(int cell);
    int getAdjacentMinesCenter(int cell);
};


#endif //INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H