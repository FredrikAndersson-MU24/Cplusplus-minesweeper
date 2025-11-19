#ifndef INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H
#define INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H
#include <memory>
#include <vector>

class GameBoard
{
public:
    GameBoard(int num_cells);
    ~GameBoard();
    void initGameBoard();

private:
    int num_cells; // Total number of cells.
    std::vector<char> columns;
    std::vector<char> rows;
    void initColumns(int grid_size);
    void initRows(int grid_size);


};


#endif //INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H