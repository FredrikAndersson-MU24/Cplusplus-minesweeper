#ifndef INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H
#define INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H
#include <memory>
#include <vector>

class GameBoard
{
public:
    GameBoard(const std::shared_ptr<int>& num_cells);
    ~GameBoard();
    void initGameBoard();

private:
    std::weak_ptr<int> num_cells;
    std::vector<char> columns;
    std::vector<char> rows;
    void initColumns(int grid_size);
    void initRows(int grid_size);


};


#endif //INDIVIDUELLT_PROJEKTARBETE_GAMEBOARD_H