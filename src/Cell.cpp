#include "../inc/Cell.h"

#include <format>
#include <iostream>
#include <memory>

int next_id = 0;

Cell::Cell() :
id(next_id), adjacentMines(0), marker("O"), has_mine(false), is_guessed(false), is_flagged(false)
{
    // std::cout << "Cell " << id << " constructed" << std::endl;
    next_id++;
}

Cell::~Cell()
{
    // std::cout << "Cell " << id << " destructed" << std::endl;
}

std::string Cell::showCell()
{
    if (has_mine && is_guessed)
    {
        marker = 'X';
    } else if (is_guessed)
    {
        marker = std::to_string(adjacentMines);
    } else if (is_flagged)
    {
        marker = 'F';
    } else if (has_mine)
    {
        marker = 'M';
    }

    return marker;
}

bool Cell::getHasMine() const
{
    return has_mine;
}


void Cell::setHasMine(bool b)
{
    has_mine = b;
};

void Cell::setIsFlagged(bool b)
{
    is_flagged = b;
}

void Cell::setMarker(const std::string& str)
{
    marker = str;
}

void Cell::setIsGuessed(bool b)
{
    is_guessed = b;
}

int Cell::getId() const
{
    return id;
}

void Cell::setAdjacentMines(int i)
{
    adjacentMines = i;
}
