#include "map.h"
#include "critter.h"
#include "tower.h"
#include "base_tower.h" 
#include "slow_tower.h"  
#include "aoe_tower.h"
#include <iostream>

// sceneryCell implementations
/**
 * @brief Displays the scenery cell.
 */
void sceneryCell::display() {
    std::cout << "S";
}

/**
 * @brief Gets the type of the cell.
 * @return The cell type.
 */
cellType sceneryCell::getCellType() {
    return SCENERY;
}

/**
 * @brief Checks if a tower can be placed on the cell.
 * @return True if a tower can be placed, false otherwise.
 */
bool sceneryCell::canPlaceTower() {
    return true;
}

/**
 * @brief Checks if a critter can move on the cell.
 * @return True if a critter can move, false otherwise.
 */
bool sceneryCell::canCritterMove() {
    return false;
}

// pathCell implementations
/**
 * @brief Displays the path cell.
 */
void pathCell::display() {
    std::cout << "P";
}

/**
 * @brief Gets the type of the cell.
 * @return The cell type.
 */
cellType pathCell::getCellType() {
    return PATH;
}

/**
 * @brief Checks if a tower can be placed on the cell.
 * @return True if a tower can be placed, false otherwise.
 */
bool pathCell::canPlaceTower() {
    return false;
}

/**
 * @brief Checks if a critter can move on the cell.
 * @return True if a critter can move, false otherwise.
 */
bool pathCell::canCritterMove() {
    return true;
}

// gameMap implementations
/**
 * @brief Constructor for the gameMap class.
 * @param r The number of rows in the map.
 * @param c The number of columns in the map.
 */
gameMap::gameMap(int r, int c) : rows(r), cols(c) {
    grid.resize(rows, std::vector<Cell*>(cols, nullptr));
}

/**
 * @brief Destructor for the gameMap class.
 */
gameMap::~gameMap() {
    for (auto& row : grid) {
        for (auto& cell : row) {
            delete cell;
            cell = nullptr;
        }
    }
}

/**
 * @brief Sets a cell in the map.
 * @param r The row of the cell.
 * @param c The column of the cell.
 * @param cell The cell to set.
 */
void gameMap::setCell(int r, int c, Cell* cell) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        delete grid[r][c];
        grid[r][c] = cell;
    }
}

/**
 * @brief Sets the entry point of the map.
 * @param r The row of the entry point.
 * @param c The column of the entry point.
 */
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

/**
 * @brief Removes the entry point of the map.
 */
void gameMap::removeEntry() {
    if (entryX != -1 && entryY != -1) {
        std::cout << "\nRemoving entry point at (" << entryX << ", " << entryY << ").\n";
        entryX = -1;
        entryY = -1;
    } else {
        std::cout << "\nNo entry point to remove.\n";
    }
}

/**
 * @brief Sets the exit point of the map.
 * @param r The row of the exit point.
 * @param c The column of the exit point.
 */
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

/**
 * @brief Removes the exit point of the map.
 */
void gameMap::removeExit() {
    if (exitX != -1 && exitY != -1) {
        std::cout << "\nRemoving exit point at (" << exitX << ", " << exitY << ").\n";
        exitX = -1;
        exitY = -1;
    } else {
        std::cout << "\nNo exit point to remove.\n";
    }
}

/**
 * @brief Checks if a critter can move to the given cell.
 * @param r The row of the cell.
 * @param c The column of the cell.
 * @return True if a critter can move, false otherwise.
 */
bool gameMap::canCritterMove(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] != nullptr) {
        return grid[r][c]->canCritterMove();
    }
    return false;
}

/**
 * @brief Checks if a tower can be placed on the given cell.
 * @param r The row of the cell.
 * @param c The column of the cell.
 * @return True if a tower can be placed, false otherwise.
 */
bool gameMap::canPlaceTower(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] != nullptr) {
        return grid[r][c]->canPlaceTower();
    }
    return false;
}

/**
 * @brief Displays the map.
 */
// Update the standard display function
void gameMap::displayMap() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == entryX && j == entryY)
                std::cout << "E";
            else if (i == exitX && j == exitY)
                std::cout << "X";
            else {
                // Check if there's a tower at this position
                Tower* tower = getTowerAt(i, j);
                if (tower) {
                    if (dynamic_cast<BasicTower*>(tower)) {
                        std::cout << "B"; // Basic tower
                    } else if (dynamic_cast<SlowTower*>(tower)) {
                        std::cout << "S"; // Slow tower
                    } else if (dynamic_cast<AoETower*>(tower)) {
                        std::cout << "A"; // AoE tower
                    } else {
                        std::cout << "T"; // Generic tower
                    }
                }
                else if (grid[i][j])
                    grid[i][j]->display();
                else
                    std::cout << ".";
            }
        }
        std::cout << "\n";
    }
}

void gameMap::displayMap(const std::vector<Critter*>& critters) const {
    // Create a grid to hold the display characters
    std::vector<std::vector<char>> displayGrid(rows, std::vector<char>(cols, '.'));

    // Fill the grid with the map's base
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == entryX && j == entryY)
                displayGrid[i][j] = 'E';
            else if (i == exitX && j == exitY)
                displayGrid[i][j] = 'X';
            else if (grid[i][j]) {
                if (grid[i][j]->getCellType() == PATH)
                    displayGrid[i][j] = 'P';
                else
                    displayGrid[i][j] = 'S';
            }
            else
                displayGrid[i][j] = '.';
            
            // Check for towers and override the display character
            Tower* tower = getTowerAt(i, j);
            if (tower) {
                if (dynamic_cast<BasicTower*>(tower)) {
                    displayGrid[i][j] = 'B'; // Basic tower
                } else if (dynamic_cast<SlowTower*>(tower)) {
                    displayGrid[i][j] = 'S'; // Slow tower
                } else if (dynamic_cast<AoETower*>(tower)) {
                    displayGrid[i][j] = 'A'; // AoE tower
                } else {
                    displayGrid[i][j] = 'T'; // Generic tower
                }
            }
        }
    }

    // Overlay the critters onto the grid (higher priority than towers)
    for (Critter* critter : critters) {
        int x = static_cast<int>(critter->getX());
        int y = static_cast<int>(critter->getY());
        if (x >= 0 && x < rows && y >= 0 && y < cols && critter->isAlive()) {
            displayGrid[x][y] = 'C'; // 'C' for Critter
        }
    }

    // Print the grid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << displayGrid[i][j];
        }
        std::cout << "\n";
    }
}

/**
 * @brief Checks if the map is valid.
 * @return True if the map is valid, false otherwise.
 */
bool gameMap::isValidMap() {
    if (entryX == -1 || exitX == -1) {
        return false;
    }
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    return isPathConnected(entryX, entryY, visited);
}

/**
 * @brief Checks if the path is connected.
 * @param x The x coordinate of the current cell.
 * @param y The y coordinate of the current cell.
 * @param visited The visited cells.
 * @return True if the path is connected, false otherwise.
 */
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

// Tower placement
bool gameMap::placeTower(int row, int col, Tower* tower) {
    // Check if position is valid for tower placement
    if (!canPlaceTower(row, col)) {
        return false;
    }
    
    // Check if there's already a tower at this location
    if (getTowerAt(row, col) != nullptr) {
        return false;
    }
    
    // Place the tower and store its position
    tower->setPosition(row, col);
    towers[std::make_pair(row, col)] = tower;
    towerLocations.push_back(std::make_pair(row, col));
    return true;
}

Tower* gameMap::removeTower(int row, int col) {
    auto pos = std::make_pair(row, col);
    auto it = towers.find(pos);
    if (it == towers.end()) {
        return nullptr;
    }
    
    Tower* tower = it->second;
    towers.erase(it);
    
    // Remove from locations vector
    towerLocations.erase(std::remove(towerLocations.begin(), towerLocations.end(), pos), 
                         towerLocations.end());
    
    return tower;
}

Tower* gameMap::getTowerAt(int row, int col) const {
    auto it = towers.find(std::make_pair(row, col));
    if (it == towers.end()) {
        return nullptr;
    }
    return it->second;
}

std::vector<Tower*> gameMap::getAllTowers() const {
    std::vector<Tower*> result;
    for (const auto& pair : towers) {
        result.push_back(pair.second);
    }
    return result;
}
