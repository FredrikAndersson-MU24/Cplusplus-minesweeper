#ifndef CELL_H
#define CELL_H


class Cell
{

public:
    Cell();
    ~Cell() = default;
    [[nodiscard]] char getMarker() const;
    void updateMarker();
    void updateMarker(char c);
    void setAdjacentMines(int i);
    [[nodiscard]] int getAdjacentMines() const;
    [[nodiscard]] int getId() const;
    void setHasMine(bool b);
    [[nodiscard]] bool hasMine() const;
    void setIsFlagged(bool b);
    [[nodiscard]] bool isFlagged() const;
    void setIsGuessed(bool b);
    [[nodiscard]] bool isGuessed() const;

private:
    int id;
    int adjacent_mines;
    char marker;
    bool has_mine;
    bool is_guessed;
    bool is_flagged;

};


#endif