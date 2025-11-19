#ifndef INDIVIDUELLT_PROJEKTARBETE_CELL_H
#define INDIVIDUELLT_PROJEKTARBETE_CELL_H
#include <string>

class Cell
{
public:
    Cell();
    ~Cell();
    char showCell() const;
    void setHasMine(bool b);
    int getId() const;

private:
    int id;
    char marker;
    bool has_mine;
    bool is_guessed;
    bool is_flagged;
};

#endif //INDIVIDUELLT_PROJEKTARBETE_CELL_H