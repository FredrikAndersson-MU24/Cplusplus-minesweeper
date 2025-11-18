#include <iostream>
#include <cmath>
#include <memory>

void initializeGameboard(const std::shared_ptr<int>& num_cells)
{
    int numbers[*num_cells + 1];
    char rowLabel = 'A';
    int colLabel = 1;
    for (int i = 1; i <= *num_cells; i++)
    {
        numbers[i] = i;
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
        {
            std::cout << "X" << " | ";
        } else // Print last col cell of row
        {
            std::cout << "X" << " |";
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
