#ifndef INDIVIDUELLT_PROJEKTARBETE_CELL_H
#define INDIVIDUELLT_PROJEKTARBETE_CELL_H
#include <memory>
#include <string>

class Cell
{
public:
    Cell();
    ~Cell();
    std::string showCell();
    void setHasMine(bool b);
    void setIsFlagged(bool b);
    void setIsGuessed(bool b);
    void setMarker(const std::string& str);
    void setAdjacentMines(int i);
    int getId() const;
    bool getHasMine() const;

private:
    int id;
    int adjacentMines;
    std::string marker;
    bool has_mine;
    bool is_guessed;
    bool is_flagged;
    // char revealAdjacentMines(int num_cells, int grid_size, int cell);
};

#endif //INDIVIDUELLT_PROJEKTARBETE_CELL_H