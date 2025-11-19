#include "../inc/Cell.h"

#include <iostream>

int next_id = 0;

Cell::Cell() :
id(next_id), marker(' '), has_mine(false), is_guessed(false), is_flagged(false)
{
    std::cout << "Cell " << id << " constructed" << std::endl;
    next_id++;
}

Cell::~Cell()
{
    std::cout << "Cell " << id << " destructed" << std::endl;
}

char Cell::showCell()
{
    return has_mine ? 'X' : 'O';
}


void Cell::setHasMine(bool b)
{
    has_mine = b;
};