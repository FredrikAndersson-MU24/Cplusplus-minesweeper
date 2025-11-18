#include <iostream>
#include <cmath>




int main ()
{
    int num_cells = 100;
    int numbers[num_cells + 1];
    char row = 'A';
    int col = 1;
    for (int i = 1; i <= num_cells; i++)
    {
        numbers[i] = i;
    }
    // Print column numbers
    std::cout << " ";
    for ( int i = 1; i <= static_cast<int>(sqrt(num_cells)); i++)
    {
        std::cout << "   " << col;
        if (i == static_cast<int>(sqrt(num_cells))) {
        std::cout << std::endl;
        }
        col++;
    }
    // Print top outline
    std::cout << "  |--";
    for ( int j = 1; j <= (static_cast<int>(sqrt(num_cells)) - 1); j++)
    {
        std::cout << "-|--";
    }
    std::cout << "-|" << std::endl;

    // Print cell grid
    for (int i = 1; i <= num_cells; i++)
    {
        if (i % static_cast<int>(sqrt(num_cells)) == 0)
        {
            std::cout << "X" << " |";
            std::cout << std::endl;
            std::cout << "  |--";
            for ( int j = 1; j <= (static_cast<int>(sqrt(num_cells)) - 1); j++)
            {
            std::cout << "-|--";
            }
            std::cout << "-|" << std::endl;
            row++;
        } else if ((i - 1) % static_cast<int>(sqrt(num_cells)) == 0)
        {
            std::cout << row <<" | X | ";
        } else
        {
            std::cout << "X" << " | ";
        }
    }

    return 0;
}
