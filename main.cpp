#include <iostream>
#include <cmath>
#include <memory>

#include "Cell.h"

void initializeGameboard( std::shared_ptr<int>& num_cells)
{
    std::shared_ptr<Cell> numbers[*num_cells + 1];
    const int grid_size = static_cast<int>(sqrt(*num_cells));
    char rowLabel = 'A';
    int colLabel = 1;
    for (int i = 1; i <= *num_cells; i++)
    {
        const std::shared_ptr<Cell> cell = std::make_shared<Cell>();
        numbers[i] = cell;
    }

    // Print column labels
    std::cout << " ";
    for ( int i = 1; i <= static_cast<int>(sqrt(*num_cells)); i++)
    {
        std::cout << "   " << colLabel;
        if (i == static_cast<int>(sqrt(*num_cells))) {
            std::cout << std::endl;
        }
        colLabel++;
    }

    // Print top outline
    std::cout << "  |--";
    for ( int j = 1; j <= (static_cast<int>(sqrt(*num_cells)) - 1); j++)
    {
        std::cout << "-|--";
    }
    std::cout << "-|" << std::endl;

    // Print cell grid
    for (int i = 1; i <= *num_cells; i++)
    {
        if ((i - 1) % static_cast<int>(sqrt(*num_cells)) == 0) // Print row label and first col cell
        {
            std::cout << rowLabel << " | X | ";
        } else if (i % static_cast<int>(sqrt(*num_cells)) != 0) // Print i:th col cell
            std::cout << rowLabel << " | " << numbers[i].get()->showCell() << " | ";
        {
            std::cout << numbers[i].get()->showCell() << " | ";
        } else // Print last col cell of row
        {
            std::cout << numbers[i].get()->showCell() << " |";
            std::cout << std::endl;
            std::cout << "  |--";
            for ( int j = 1; j <= (static_cast<int>(sqrt(*num_cells)) - 1); j++)
            {
                std::cout << "-|--";
            }
            std::cout << "-|" << std::endl;
            rowLabel++;
        }
    }
}


int main ()
{
    std::shared_ptr<int> num_cells = std::make_shared<int>();
    std::cout << "Select grid size" << std::endl;
    std::cin >> *num_cells; // TODO Implement input validation. Except only integers that are perfect squares
    initializeGameboard(num_cells);

    return 0;
}
