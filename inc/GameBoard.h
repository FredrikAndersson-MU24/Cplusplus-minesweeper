#ifndef INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H
#define INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H
#include <memory>
#include <vector>

#include "Cell.h"

class GameBoard
{
public:
    GameBoard(int num_cells);
    ~GameBoard();
    void printGameBoard();
    void initGameBoard();
    void findCell(char input[]);

private:
    int num_cells; // Total number of cells.
    std::vector<char> columns;
    std::vector<char> rows;
    std::vector<std::shared_ptr<Cell>> cells;
    int grid_size; // Sqrt of num_cells. To set num of rows and columns.
    void initColumns();
    void initRows();
    void initCells();


};


#endif //INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H