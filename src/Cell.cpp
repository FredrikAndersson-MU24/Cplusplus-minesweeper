#include "../inc/Cell.h"

#include <iostream>

int next_id = 0;

Cell::Cell() :
id(next_id), marker('X'), has_mine(false), guessed_mine(false), marked_mine(false)
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
    marker = 'o';
    return marker;
}


void Cell::setHasMine(bool b)
{
    has_mine = b;
};