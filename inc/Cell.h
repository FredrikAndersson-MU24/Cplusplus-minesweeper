#ifndef INDIVIDUELLT_PROJEKTARBETE_CELL_H
#define INDIVIDUELLT_PROJEKTARBETE_CELL_H
#include <memory>
#include <string>

class Cell
{
public:
    Cell();
    ~Cell();
    char showCell();
    void setHasMine(bool b);
    void setIsFlagged(bool b);
    void setIsGuessed(bool b, const std::shared_ptr<bool>& running, int num_cells, int grid_size);
    int getId() const;

private:
    int id;
    char marker;
    bool has_mine;
    bool is_guessed;
    bool is_flagged;
    // char revealAdjacentMines(int num_cells, int grid_size, int cell);
};

#endif //INDIVIDUELLT_PROJEKTARBETE_CELL_H