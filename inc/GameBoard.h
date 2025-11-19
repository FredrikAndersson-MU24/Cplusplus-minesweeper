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
    void findCell(const char input[]) const;

private:
    int num_cells; // Total number of cells.
    std::vector<char> columns;
    std::vector<char> rows;
    std::vector<std::shared_ptr<Cell>> cells;
    int grid_size; // Sqrt of num_cells. To set num of rows and columns.
    int num_mines;
    void initColumns();
    void initRows();
    void initCells();
    void randomizeMines() const;


};


#endif //INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H