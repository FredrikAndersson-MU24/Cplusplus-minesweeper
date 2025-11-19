#include "GameBoard.h"
#include "Cell.h"

#include <cmath>
#include <iostream>



GameBoard::GameBoard(int cells) : num_cells(cells),
    grid_size(static_cast<int>(std::sqrt(cells)))
{
    std::cout << "Game board constructed" << std::endl;
}

GameBoard::~GameBoard() {
    std::cout << "Game board deconstructed" << std::endl;
}

void GameBoard::initGameBoard()
{
    initColumns();
    initRows();
    initCells();
}

{
    const std::shared_ptr<int> cells = num_cells.lock();
    std::cout << "num_cells : " << num_cells.lock() << std::endl;
    std::shared_ptr<Cell> numbers[*cells + 1];
    const int grid_size = static_cast<int>(std::sqrt(*cells));
    initColumns(grid_size);
    initRows(grid_size);
    for (int i = 1; i <= *cells; i++)
    {
        const std::shared_ptr<Cell> cell = std::make_shared<Cell>();
        numbers[i] = cell;
    }

    // Print column labels
    std::cout << " ";
    for ( int i = 1; i <= grid_size; i++)
    {
        std::cout << "   " << columns.at(i-1);
        if (i == grid_size) {
            std::cout << std::endl;
        }
    }

    // Print top outline
    std::cout << "  |--";
    for ( int j = 1; j <= grid_size - 1; j++)
    {
        std::cout << "-|--";
    }
    std::cout << "-|" << std::endl;

    // Print cell grid
    for (int i = 1; i <= *cells; i++)
    {
        if ((i - 1) % grid_size == 0) // Print row label and first col cell
        {
            std::cout << rows.at(i-1) << " | " << numbers[i].get()->showCell() << " | ";
        } else if (i % grid_size != 0) // Print i:th col cell
        {
            std::cout << numbers[i].get()->showCell() << " | ";
        } else // Print last col cell of row
        {
            std::cout << numbers[i].get()->showCell() << " |";
            std::cout << std::endl;
            std::cout << "  |--";
            for ( int j = 1; j <= grid_size - 1; j++)
            {
                std::cout << "-|--";
            }
            std::cout << "-|" << std::endl;
        }
    }
}

// Populating the columns vector with the correct number
// of column labels given the grid_size parameter.
void GameBoard::initColumns()
{
    char colLabel = 1;
    for ( int i = 1; i <= grid_size; i++)
    {
        columns.push_back(colLabel);
        colLabel++;
    }
    std::cout << "columns initiated : " << columns.size() << std::endl;
}

// Populating the rows vector with the correct number
// of row labels given the grid_size parameter.
void GameBoard::initRows()
{
    char rowLabel = 'A';
    for ( int i = 1; i <= grid_size; i++)
    {
        rows.push_back(rowLabel);
        rowLabel++;
    }
    std::cout << "rows initiated : " << rows.size() << std::endl;
    for (char row : rows)
    {
        std::cout << row << std::endl;
    }
}

void GameBoard::initCells()
{
    for (int i = 1; i <= num_cells; i++)
    {
        const std::shared_ptr<Cell> cell = std::make_shared<Cell>();
        cells.emplace_back(cell);
    }
}
