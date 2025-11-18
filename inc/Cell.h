#ifndef INDIVIDUELLT_PROJEKTARBETE_CELL_H
#define INDIVIDUELLT_PROJEKTARBETE_CELL_H
#include <string>

class Cell
{
public:
    Cell();
    ~Cell();
    char showCell();
    void setHasMine(bool b);

private:
    int id;
    char marker;
    bool has_mine;
    bool guessed_mine;
    bool marked_mine;
};

#endif //INDIVIDUELLT_PROJEKTARBETE_CELL_H