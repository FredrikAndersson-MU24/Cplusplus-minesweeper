#include "GameBoard.h"
#include "Cell.h"

#include <cmath>
#include <functional>
#include <iostream>
#include <random>


GameBoard::GameBoard(int cells) :
num_cells(cells),
grid_size(static_cast<int>(std::sqrt(cells))),
num_mines(grid_size),
revealed_cells(0)
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

void GameBoard::printGameBoard() const
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
    int colLabel = 1;
    for ( int i = 1; i <= grid_size; i++)
    {
        columns.push_back(colLabel);
        colLabel++;
    }
    // std::cout << "columns initiated : " << columns.size() << std::endl;
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
    // std::cout << "rows initiated : " << rows.size() << std::endl;
    // for (char row : rows)
    // {
    //     std::cout << row << std::endl;
    // }
}

int GameBoard::findCell(const char* coord)
{
    char row = 0;
    std::string col_as_string;
    while (*coord)
    {
        char temp = *coord;
        if (std::isalpha(temp))
        {
            row = static_cast<char>(toupper(temp));
        }
        if (std::isdigit(temp))
        {
            col_as_string.push_back(temp);
        }
        coord++;
    }
    const int col_as_int = stoi(col_as_string);

    int row_index = 0;
    int col_index = 0;
    for (char c : rows)
    {
        if (c == row)
        {
            break;
        }
        row_index++;
    }
    for (int i : columns)
    {
        if (i == col_as_int)
        {
            break;
        }
        col_index++;
    }
    const int cell = row_index * grid_size + col_index;
    std::cout << "ROW INDEX: " << row_index << std::endl;
    std::cout << "COL INDEX: " << col_index << std::endl;
    getPlacement(row_index, col_index);
    return cell;
}

void GameBoard::initCells()
{
    for (int i = 1; i <= num_cells; i++)
    {
        const std::shared_ptr<Cell> cell = std::make_shared<Cell>();
        cells.emplace_back(cell);
    }
}

void GameBoard::randomizeMines() const
{
    int range = num_cells - 1;
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> uniform_dist(0, range);
    int mines[grid_size];
    for (int i = 0; i < grid_size; i++)
    {
        int mean = uniform_dist(e);
            for (int mine : mines)
            {
                while (mine == mean)
                {
                    mean = uniform_dist(e);
                }
            }
        mines[i] = mean;
    }
    for (const int mine : mines)
    {
        cells.at(mine)->setHasMine(true);
    }
}

void GameBoard::getPlacement(int row_index, int col_index)
{
    if (row_index == 0)
    {
        placement = Placement::TOP;
        if (col_index == 0)
        {
            placement = Placement::TOP_LEFT;
        }
        if (col_index == columns.size() - 1)
        {
            placement = Placement::TOP_RIGHT;
        }
    } else if (row_index == rows.size() - 1)
    {
        placement = Placement::BOTTOM;
        if (col_index == 0)
        {
            placement = Placement::BOTTOM_LEFT;
        }
        if (col_index == columns.size() - 1)
        {
            placement = Placement::BOTTOM_RIGHT;
        }
    } else if (col_index == 0)
    {
        placement = Placement::LEFT;
    } else if (col_index == columns.size() - 1)
    {
        placement = Placement::RIGHT;
    } else
    {
        placement = Placement::CENTER;
    }
}

void GameBoard::getAdjacentMines(const int cell)
{
    int adjacent = 0;
    switch (placement)
    {
    case Placement::LEFT:
        adjacent = getAdjacentMinesLeft(cell);
        break;
    case Placement::RIGHT:
        adjacent = getAdjacentMinesRight(cell);
        break;
    case Placement::TOP_RIGHT:
        adjacent = getAdjacentMinesTopRight(cell);
        break;
    case Placement::BOTTOM_RIGHT:
        adjacent = getAdjacentMinesBottomRight(cell);
        break;
    case Placement::TOP_LEFT:
        adjacent = getAdjacentMinesTopLeft(cell);
        break;
    case Placement::BOTTOM_LEFT:
        adjacent = getAdjacentMinesBottomLeft(cell);
        break;
    case Placement::TOP:
        adjacent = getAdjacentMinesTop(cell);
        break;
    case Placement::BOTTOM:
        adjacent = getAdjacentMinesBottom(cell);
        break;
    case Placement::CENTER:
        adjacent = getAdjacentMinesCenter(cell);
        break;
    default: ;
    }
    std::cout << "ADJACENT : " << adjacent << std::endl;
    cells.at(cell).get()->setAdjacentMines(adjacent);
}

//
// void GameBoard::validateCell(const char* coord)
// {
//     //The first character is the row
//     //The second character is the column
//     char first_char = input[0];
//     char second_char = input[1];
//     int char_1 = 0;
//     int char_2 = 0;
//     for (char c : rows)
//     {
//         if (c == first_char)
//         {
//             break;
//         }
//         char_1++;
//     }
//     for (char c : columns)
//     {
//         if (c == second_char)
//         {
//             break;
//         }
//         char_2++;
//     }
//     const int cell = char_1 * grid_size - 1 + char_2;
//     std::cout << "char 1 : " << char_1 << std::endl;
//     std::cout << "char 2 : " << char_2 << std::endl;
//     std::cout << "char 1 : " << char_1 << " * grid_size  + " << "char 2 : " << char_2 << " = " << char_1 * grid_size-1 + char_2 << std::endl;
//     std::cout << "cell at : " << cell << " = " << cells.at(cell).get()->getId() << std::endl;
// }



std::vector<std::shared_ptr<Cell>> GameBoard::getCells()
{
    return cells;
}

GameBoard::GameStatus GameBoard::checkGameStatus(int cell)
{
    GameStatus response = GameStatus::ACTIVE;
    if (cells.at(cell)->hasMine() && cells.at(cell)->isFlagged())
    {
        response = GameStatus::ACTIVE;
    }
    if (cells.at(cell)->hasMine())
    {
        response = GameStatus::LOSS;
    }
    if (num_cells - num_mines == revealed_cells)
    {
        response = GameStatus::WIN;
    }
    return response;
}

void GameBoard::flagCell(int cell)
{
    cells.at(cell)->setIsFlagged(true);
}

void GameBoard::revealCell(int cell)
{
    cells.at(cell)->setIsGuessed(true);
    revealed_cells++;
}

std::vector<int> GameBoard::getColumns()
{
    return columns;
}

std::vector<char> GameBoard::getRows()
{
    return rows;
}

bool GameBoard::hasAdjacentMineAtMinusGridSizeMinusOne(const int cell) const
{
    return cells.at(cell-grid_size-1).get()->hasMine();
}

bool GameBoard::hasAdjacentMineAtMinusGridSize(const int cell) const
{
    return cells.at(cell-grid_size).get()->hasMine();
}

bool GameBoard::hasAdjacentMineAtMinusGridSizePlusOne(const int cell) const
{
    return cells.at(cell-grid_size+1).get()->hasMine();
}

bool GameBoard::hasAdjacentMineAtMinusOne(const int cell) const
{
    return cells.at(cell-1).get()->hasMine();
}

bool GameBoard::hasAdjacentMineAtPlusOne(const int cell) const
{
    return cells.at(cell-1).get()->hasMine();
}

bool GameBoard::hasAdjacentMineAtPlusGridSizeMinusOne(const int cell) const
{
    return cells.at(cell+grid_size-1).get()->hasMine();
}
bool GameBoard::hasAdjacentMineAtPlusGridSize(const int cell) const
{
    return cells.at(cell+grid_size).get()->hasMine();
}

bool GameBoard::hasAdjacentMineAtPlusGridSizePlusOne(int cell)
{
    return cells.at(cell+grid_size+1).get()->hasMine();
}

int GameBoard::getAdjacentMinesTopLeft(const int cell)
{
    int adjacent = 0;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizePlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesLeft(const int cell)
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSizePlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizePlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesRight(const int cell)
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesTopRight(const int cell)
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesBottomRight(const int cell)
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesBottomLeft(const int cell)
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSizePlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesTop(const int cell)
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizePlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesBottom(const int cell)
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSizePlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesCenter(const int cell)
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSizePlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizePlusOne(cell)) adjacent++;
    return adjacent;
}