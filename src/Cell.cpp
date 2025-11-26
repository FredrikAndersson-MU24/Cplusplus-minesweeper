#include "../inc/Cell.h"

#include <format>

int next_id = 0;

Cell::Cell() :
id(next_id), adjacent_mines(0), marker(' '), has_mine(false), is_guessed(false), is_flagged(false)
{
    next_id++;
}

char Cell::getMarker() const
{
    return marker;
}

bool Cell::hasMine() const
{
    return has_mine;
}


void Cell::setHasMine(const bool b)
{
    has_mine = b;
};

void Cell::setIsFlagged(const bool b)
{
    is_flagged = b;
}

void Cell::updateMarker()
{
    if (has_mine && is_guessed)
    {
        marker = 'X';
    } else if (is_guessed)
    {
        marker = std::to_string(adjacent_mines)[0];
    } else if (is_flagged)
    {
        marker = 'F';
    }
}

void Cell::updateMarker(const char c)
{
    marker = c;
}

void Cell::setIsGuessed(const bool b)
{
    is_guessed = b;
}

int Cell::getId() const
{
    return id;
}

void Cell::setAdjacentMines(const int i)
{
    adjacent_mines = i;
}

int Cell::getAdjacentMines() const
{
    return adjacent_mines;
}

bool Cell::isFlagged() const
{
    return is_flagged;
}

bool Cell::isGuessed() const
{
    return is_guessed;
}
