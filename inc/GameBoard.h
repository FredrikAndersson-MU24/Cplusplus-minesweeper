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
    // int validateCell(const char* coord);
    void userChoice(const char* coord, int choice, const std::shared_ptr<bool>& running);

private:
    int num_cells; // Total number of cells.
    std::vector<int> columns;
    std::vector<char> rows;
    std::vector<std::shared_ptr<Cell>> cells;
    int grid_size; // Sqrt of num_cells. To set num of rows and columns.
    int num_mines;
    enum class Placement {LEFT, RIGHT, TOP, BOTTOM, TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT, CENTER};
    Placement placement{};
    void initColumns();
    void initRows();
    void initCells();
    void randomizeMines() const;
    void getPlacement(int row_index, int col_index);
    void getAdjacentMines(int cell) const;


};


#endif //INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H