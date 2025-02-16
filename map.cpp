#include "map.h"
#include <iostream>

// sceneryCell implementations
void sceneryCell::display() {
    std::cout << "S";
}

cellType sceneryCell::getCellType() {
    return SCENERY;
}

bool sceneryCell::canPlaceTower() {
    return true;
}

bool sceneryCell::canCritterMove() {
    return false;
}

// pathCell implementations
void pathCell::display() {
    std::cout << "P";
}

cellType pathCell::getCellType() {
    return PATH;
}

bool pathCell::canPlaceTower() {
    return false;
}

bool pathCell::canCritterMove() {
    return true;
}

// gameMap implementations
gameMap::gameMap(int r, int c) : rows(r), cols(c) {
    grid.resize(rows, std::vector<Cell*>(cols, nullptr));
}

gameMap::~gameMap() {
    for (auto& row : grid) {
        for (auto& cell : row) {
            delete cell;
            cell = nullptr;
        }
    }
}

void gameMap::setCell(int r, int c, Cell* cell) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        delete grid[r][c];
        grid[r][c] = cell;
    }
}

void gameMap::setEntry(int r, int c) {
    if (entryX != -1 && entryY != -1) {
        std::cout << "Error: An entry point already exists at (" << entryX << ", " << entryY << "). Cannot add another entry point.\n";
        return;
    }
    if (grid[r][c] == nullptr) {
        std::cout << "Error: Cannot set entry to an empty cell.\n";
        return;
    }
    if (grid[r][c]->getCellType() != PATH) {
        std::cout << "Error: Entry must be placed on a PATH cell.\n";
        return;
    }
    entryX = r;
    entryY = c;
}

void gameMap::removeEntry() {
    if (entryX != -1 && entryY != -1) {
        std::cout << "\nRemoving entry point at (" << entryX << ", " << entryY << ").\n";
        entryX = -1;
        entryY = -1;
    } else {
        std::cout << "\nNo entry point to remove.\n";
    }
}

void gameMap::setExit(int r, int c) {
    if (exitX != -1 && exitY != -1) {
        std::cout << "Error: An exit point already exists at (" << exitX << ", " << exitY << "). Cannot add another exit point.\n";
        return;
    }
    if (grid[r][c] == nullptr) {
        std::cout << "Error: Cannot set exit to an empty cell.\n";
        return;
    }
    if (grid[r][c]->getCellType() != PATH) {
        std::cout << "Error: Exit must be placed on a PATH cell.\n";
        return;
    }
    exitX = r;
    exitY = c;
}

void gameMap::removeExit() {
    if (exitX != -1 && exitY != -1) {
        std::cout << "\nRemoving exit point at (" << exitX << ", " << exitY << ").\n";
        exitX = -1;
        exitY = -1;
    } else {
        std::cout << "\nNo exit point to remove.\n";
    }
}

bool gameMap::canCritterMove(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] != nullptr) {
        return grid[r][c]->canCritterMove();
    }
    return false;
}

bool gameMap::canPlaceTower(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] != nullptr) {
        return grid[r][c]->canPlaceTower();
    }
    return false;
}

void gameMap::displayMap() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == entryX && j == entryY)
                std::cout << "E";
            else if (i == exitX && j == exitY)
                std::cout << "X";
            else if (grid[i][j])
                grid[i][j]->display();
            else
                std::cout << ".";
        }
        std::cout << "\n";
    }
}

bool gameMap::isValidMap() {
    if (entryX == -1 || exitX == -1) {
        return false;
    }
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    return isPathConnected(entryX, entryY, visited);
}

bool gameMap::isPathConnected(int x, int y, std::vector<std::vector<bool>>& visited) {
    if (x == exitX && y == exitY) {
        return true;
    }
    if (x < 0 || x >= rows || y < 0 || y >= cols || visited[x][y] || 
        grid[x][y] == nullptr || grid[x][y]->getCellType() != PATH) {
        return false;
    }
    visited[x][y] = true;
    return isPathConnected(x + 1, y, visited) || 
           isPathConnected(x - 1, y, visited) ||
           isPathConnected(x, y + 1, visited) || 
           isPathConnected(x, y - 1, visited);
}