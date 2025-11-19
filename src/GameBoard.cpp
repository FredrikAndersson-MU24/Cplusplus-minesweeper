#include "GameBoard.h"
#include "Cell.h"

#include <cmath>
#include <functional>
#include <iostream>
#include <random>


GameBoard::GameBoard(int cells) :
num_cells(cells),
grid_size(static_cast<int>(std::sqrt(cells))),
num_mines(grid_size)
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
    randomizeMines();
}

void GameBoard::printGameBoard()
{
    int rowCounter = 0; // Counter to extract the correct row label

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
    for (int i = 1; i <= num_cells; i++)
    {
        if ((i - 1) % grid_size == 0) // Print row label and first col cell
        {
            std::cout << rows.at(rowCounter) << " | " << cells.at(i - 1).get()->showCell() << " | ";
            rowCounter++;
        } else if (i % grid_size != 0) // Print i:th col cell
        {
            std::cout << cells.at(i - 1).get()->showCell() << " | ";
        } else // Print last col cell of row
        {
            std::cout << cells.at(i - 1).get()->showCell() << " |";
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
    char colLabel = '1';
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

void GameBoard::findCell(char input[])
{
    //The first character is the row
    //The second character is the column
    char first_char = input[0];
    char second_char = input[1];
    int char_1 = 0;
    int char_2 = 0;
    for (char c : rows)
    {
        if (c == first_char)
        {
            break;
        }
        char_1++;
    }
    for (char c : columns)
    {
        if (c == second_char)
        {
            break;
        }
        char_2++;
    }
    const int cell = char_1 * grid_size - 1 + char_2;
    std::cout << "char 1 : " << char_1 << std::endl;
    std::cout << "char 2 : " << char_2 << std::endl;
    std::cout << "char 1 : " << char_1 << " * grid_size  + " << "char 2 : " << char_2 << " = " << char_1 * grid_size-1 + char_2 << std::endl;
    std::cout << "cell at : " << cell << " = " << cells.at(cell).get()->getId() << std::endl;
}

void GameBoard::initCells()
{
    for (int i = 1; i <= num_cells; i++)
    {
        const std::shared_ptr<Cell> cell = std::make_shared<Cell>();
        cells.emplace_back(cell);
    }
}

void GameBoard::randomizeMines()
{
    int range = num_cells;
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> uniform_dist(0, range);
    int mines[num_mines];

    // std::cout << "Randomize: " << std::endl;
    for (int i = 0; i < num_mines; i++)
    {
        int mean = uniform_dist(e);
        bool duplicate = false;
            for (int mine : mines)
            {
                while (mine == mean)
                {
                    // std::cout << "DUPLICATE : " << mean << std::endl;
                    mean = uniform_dist(e);
                    // std::cout << "NEW : " << mean << std::endl;
                }
            }
        mines[i] = mean;
    }
    for (int mine : mines)
    {
        std::cout << "mine id " << mine << std::endl;
        cells.at(mine)->setHasMine(true);
    }

}
