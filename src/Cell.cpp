#include "../inc/Cell.h"

#include <iostream>
#include <memory>

int next_id = 0;

Cell::Cell() :
id(next_id), marker('O'), has_mine(false), is_guessed(false), is_flagged(false)
{
    // std::cout << "Cell " << id << " constructed" << std::endl;
    next_id++;
}

Cell::~Cell()
{
    // std::cout << "Cell " << id << " destructed" << std::endl;
}

char Cell::showCell()
{
    if (is_flagged)
    {
        marker = 'F';
    }
    if (is_guessed)
    {
        marker = 'o';
    }
    if (has_mine && is_guessed)
    {
        marker = 'X';
    }
    return marker;
}


void Cell::setHasMine(bool b)
{
    has_mine = b;
};

void Cell::setIsFlagged(bool b)
{
    is_flagged = b;
}

void Cell::setIsGuessed(bool b, const std::shared_ptr<bool>& running, int num_cells, int grid_size)
{
    is_guessed = b;
    // std::cout << "Has mine : " << has_mine << std::endl;
    // std::cout << "Is guessed : " << is_guessed << std::endl;
    if (is_guessed && has_mine)
    {
        *running = false;
    }
    std::cout << "ID : " << id << std::endl;
    // revealAdjacentMines(num_cells, grid_size);
}

int Cell::getId() const
{
    return id;
}
//
// char Cell::revealAdjacentMines(int num_cells, int grid_size)
// {
//
//
//
// }
