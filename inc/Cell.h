#ifndef CELL_H
#define CELL_H

#include <string>


class Cell
{
public:
    Cell();
    ~Cell() = default;
    std::string getMarker();
    void updateMarker();
    void updateMarker(char c);
    void setAdjacentMines(int i);
    [[nodiscard]] int getId() const;
    void setHasMine(bool b);
    [[nodiscard]] bool hasMine() const;
    void setIsFlagged(bool b);
    [[nodiscard]] bool isFlagged() const;
    void setIsGuessed(bool b);
    [[nodiscard]] bool isGuessed() const;

private:
    int id;
    int adjacentMines;
    std::string marker;
    bool has_mine;
    bool is_guessed;
    bool is_flagged;
};


#endif