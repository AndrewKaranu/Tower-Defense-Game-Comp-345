#include "map.h"
#include <iostream>
#include <queue>

// Constructor to create a grid with empty cells
Map::Map(int r, int c) : rows(r), cols(c) {
    grid.resize(rows, std::vector<Cell*>(cols, nullptr));
}

// Destructor to clean up dynamically allocated cells
Map::~Map() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete grid[i][j];
        }
    }
}

// Observer methods
void Map::addObserver(Observer* obs) {
    observers.insert(obs);
}

void Map::removeObserver(Observer* obs) {
    observers.erase(obs);
}

void Map::notifyObservers() {
    for (auto* obs : observers) {
        obs->update();
    }
}

int Map::getRows() const{
    return rows;
}

int Map::getCols() const{
    return cols;
}

// Set a cell at the specified position
void Map::setCell(int r, int c, Cell* cell) {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        delete grid[r][c];
        grid[r][c] = cell;
        notifyObservers();
    }
}

// Get the cell type at the specified position
Cell* Map::getCell(int r, int c) const {
    if (r >= 0 && r < rows && c >= 0 && c < cols) {
        return grid[r][c];  // Return cell type
        std::cout << "Cell at (" + std::to_string(r) + ", " + std::to_string(c) + "): "
                  << grid[r][c]->getCellType() << std::endl;
    }
    return nullptr;
}

// Set entry coordinates
void Map::setEntry(int r, int c) {
    if (entryCoords != std::vector<int>{-1, -1}){
        std::cout << "Error: An entry point already exists.\n";
        return;
    }
    if (grid[r][c] == nullptr || grid[r][c]->getCellType() != "Path") {
        std::cout << "Error: Entry must be placed on a PATH cell.\n";
        return;
    }
    entryCoords = {r, c};
    delete grid[r][c];
    setCell(r, c, new PathCell(r, c));
    notifyObservers();
}


// Get the entry coordinates
std::vector<int> Map::getEntry() const {
    return entryCoords;
}

// Remove entry point
void Map::removeEntry() {
    setCell(entryCoords[0], entryCoords[1], nullptr);
    entryCoords = {-1, -1};
    notifyObservers();
}

// Set exit coordinates
void Map::setExit(int r, int c) {
    if (exitCoords != std::vector<int>{-1, -1}){
        std::cout << "Error: An exit point already exists.\n";
        return;
    }
    if (grid[r][c] == nullptr || grid[r][c]->getCellType() != "Path") {
        std::cout << "Error: Exit must be placed on a PATH cell.\n";
        return;
    }
    exitCoords = {r, c};
    delete grid[r][c];
    setCell(r, c, new PathCell(r, c));
    notifyObservers();
}

// Get the exit coordinates
std::vector<int> Map::getExit() const {
    return exitCoords;
}

// Remove exit point
void Map::removeExit() {
    setCell(exitCoords[0], exitCoords[1], nullptr);
    exitCoords = {-1, -1};
    notifyObservers();
}

// Validate if the path is valid
bool Map::isValidPath() {
    if (entryCoords == std::vector<int>{-1, -1} || exitCoords == std::vector<int>{-1, -1}) {
        return false; // No entry or exit defined
    }

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::queue<std::pair<int, int>> q;
    q.push({entryCoords[0], entryCoords[1]});
    visited[entryCoords[0]][entryCoords[1]] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // Check all four directions
        std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny]) {
                if (grid[nx][ny] && grid[nx][ny]->getCellType() == "Path") {
                    if (nx == exitCoords[0] && ny == exitCoords[1]) {
                        return true; // Exit found
                    }
                    q.push({nx, ny});
                    visited[nx][ny] = true;
                }
            }
        }
    }
    return false; // No valid path found
}

// Display the map (for testing)
void Map::display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]) {
                std::cout << grid[i][j]->getCellType()[0] << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}
