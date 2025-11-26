#include "GameBoard.h"
#include "Cell.h"
#include "InputHandlers.h"

#include <charconv>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>




GameBoard::GameBoard(int cells) :
num_cells(cells),
grid_size(static_cast<int>(std::sqrt(cells))),
num_mines(grid_size),
revealed_cells(0),
game_status(GameStatus::ACTIVE)
{
}

GameBoard::GameBoard(const int num_cells, const int revealed_cells) :
num_cells(num_cells),
grid_size(static_cast<int>(std::sqrt(num_cells))),
num_mines(grid_size),
revealed_cells(revealed_cells),
game_status(GameStatus::ACTIVE)
{
}

// Takes a shared pointer reference to a GameBoard object.
// Initialises all necessary parameters to make it game ready.
void GameBoard::initGameBoard(std::shared_ptr<GameBoard>& game_board, int size)
{
    game_board = std::make_shared<GameBoard>(size);
    game_board->initColumns();
    game_board->initRows();
    game_board->initCells();
    game_board->randomizeMines();
}

void GameBoard::saveGame()
{
    const std::string filename = "./saved_game.txt";
    std::ofstream file(filename);
    if(!file.is_open())
    {
        std::cout << "COULD NOT OPEN FILE" << std::endl;
        return;
    };
    file << num_cells << "\n";
    file << revealed_cells << "\n";
    for (const std::shared_ptr<Cell>& cell : cells) {
        file << cell->hasMine() << " "
             << cell->isFlagged() << " "
             << cell->isGuessed() << " "
             << (cell->getMarker() == ' ' ? '_' : cell->getMarker()) << " "
             << cell->getAdjacentMines() << "\n";
        }
    file.close();
    std::cout << (file.is_open() ? "File open" : "File closed") << "\n\n";
    std::cout << "GAME HAS BEEN SAVED!" << std::endl;

}

bool GameBoard::loadGame(std::shared_ptr<GameBoard>& game_board)
{
    const std::string filename = "./saved_game.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "COULD NOT OPEN FILE" << std::endl;
        return false;
    }
    std::cout << "LOADING GAME..." << std::endl;
    int nc, rc;
    if (!(file >> nc >> rc))
    {
        std::cout << "CORRUPT FILE" << std::endl;
        return false;
    }
    game_board = std::make_shared<GameBoard>(nc, rc);
    game_board->initRows();
    game_board->initColumns();
    game_board->initCells();
    for (const std::shared_ptr<Cell>& cell : game_board.get()->getCells()) {
        bool has_mine, is_flagged, is_guessed;
        int adjacent;
        char marker;
        if (!(file >> has_mine >> is_flagged >> is_guessed >> marker >> adjacent))
        {
            std::cout << "CORRUPT FILE" << std::endl;
            return false;
        }
        cell->setHasMine(has_mine);
        cell->setIsFlagged(is_flagged);
        cell->setIsGuessed(is_guessed);
        marker == '_' ? cell->updateMarker(' ') : cell->updateMarker(marker);
        cell->setAdjacentMines(adjacent);
    }
    file.close();
    std::cout << (file.is_open() ? "File open" : "File closed") << "\n\n";
    std::cout << "GAME HAS BEEN LOADED!" << std::endl;
    return true;
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
            std::cout << rows.at(rowCounter) << " | " << cells.at(i - 1).get()->getMarker() << " | ";
            rowCounter++;
        } else if (i % grid_size != 0) // Print i:th col cell
        {
            std::cout << cells.at(i - 1).get()->getMarker() << " | ";
        } else // Print last col cell of row
        {
            std::cout << cells.at(i - 1).get()->getMarker() << " |";
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
}

std::vector<std::shared_ptr<Cell>> GameBoard::getCells()
{
    return cells;
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
}

// Given the coordinate, returns the index of
// the cell from the vector of cells as int
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
    setPlacement(row_index, col_index);
    return cell;
}

// Create the chosen number of cells
// and add them to the vector of cells.
void GameBoard::initCells()
{
    for (int i = 1; i <= num_cells; i++)
    {
        const std::shared_ptr<Cell> cell = std::make_shared<Cell>();
        cells.emplace_back(cell);
    }
}

// Randomize placement of mines on the grid.
// Number of mines = grid_size.
void GameBoard::randomizeMines() const
{
    int range = num_cells - 1;
    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> uniform_dist(0, range);
    std::vector<int> mines;
    for (int i = 0; i < grid_size; i++)
    {
        int mean = uniform_dist(e);
            for (const int mine : mines)
            {
                while (mine == mean)
                {
                    mean = uniform_dist(e);
                }
            }
        mines.push_back(mean);
    }
    for (const int mine : mines)
    {
        cells.at(mine)->setHasMine(true);
    }
}

// Sets the placement of the cell on the board.
void GameBoard::setPlacement(const int row_index, const int col_index)
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

// Finds cells adjacent to the chosen cell on the board
// and sets adjacent_mines to the number of mines found.
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
    cells.at(cell).get()->setAdjacentMines(adjacent);
}

GameBoard::GameStatus GameBoard::getGameStatus() const
{
    return game_status;
}

// Updates game_status if WIN or LOSS conditions are met.
void GameBoard::updateGameStatus()
{
    for (const std::shared_ptr<Cell>& cell : cells)
    {
        if (cell->isGuessed() && cell->hasMine())
        {
            game_status = GameStatus::LOSS;
        }
    }
    if (num_cells - num_mines == revealed_cells)
    {
        game_status = GameStatus::WIN;
    }
}

void GameBoard::flagCell()
{
    const std::string coord = getValidCoordinate(getRows(), getColumns());
    const int cell = findCell(coord.c_str());
    cells.at(cell)->setIsFlagged(true);
    cells.at(cell)->updateMarker();
    updateGameStatus();
}

void GameBoard::revealCell()
{
    const std::string coord = getValidCoordinate(getRows(), getColumns());
    const int cell = findCell(coord.c_str());
    if (cells.at(cell)->isGuessed()) // If cell has already been guessed, dont add to revealed_cells.
    {
        return;
    }
    getAdjacentMines(cell);
    cells.at(cell)->setIsGuessed(true);
    cells.at(cell)->updateMarker();
    revealed_cells++;
    updateGameStatus();
}

void GameBoard::revealAllMines() const
{
    for (const std::shared_ptr<Cell>& cell : cells)
    {
        if (cell->hasMine())
        {
            cell->updateMarker('X');
        }
    }
}

void GameBoard::endGame(const std::string& prompt) const
{
    revealAllMines();
    printGameBoard();
    std::cout << prompt << std::endl;
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
    return cells.at(cell+1).get()->hasMine();
}

bool GameBoard::hasAdjacentMineAtPlusGridSizeMinusOne(const int cell) const
{
    return cells.at(cell+grid_size-1).get()->hasMine();
}
bool GameBoard::hasAdjacentMineAtPlusGridSize(const int cell) const
{
    return cells.at(cell+grid_size).get()->hasMine();
}

bool GameBoard::hasAdjacentMineAtPlusGridSizePlusOne(const int cell) const
{
    return cells.at(cell+grid_size+1).get()->hasMine();
}

int GameBoard::getAdjacentMinesTopLeft(const int cell) const
{
    int adjacent = 0;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizePlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesLeft(const int cell) const
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSizePlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizePlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesRight(const int cell) const
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesTopRight(const int cell) const
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesBottomRight(const int cell) const
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesBottomLeft(const int cell) const
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSizePlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesTop(const int cell) const
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtPlusGridSizePlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesBottom(const int cell) const
{
    int adjacent = 0;
    if (hasAdjacentMineAtMinusGridSizeMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSize(cell)) adjacent++;
    if (hasAdjacentMineAtMinusGridSizePlusOne(cell)) adjacent++;
    if (hasAdjacentMineAtMinusOne(cell)) adjacent++;
    if (hasAdjacentMineAtPlusOne(cell)) adjacent++;
    return adjacent;
}

int GameBoard::getAdjacentMinesCenter(const int cell) const
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
