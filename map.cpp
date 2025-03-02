#include "map.h"
#include <iostream>
#include <SFML/Graphics.hpp>

// sceneryCell implementations
void sceneryCell::display(sf::RenderWindow& window, float x, float y) {
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(100, 100, 100)); // Gray for scenery
    window.draw(shape);
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
void pathCell::display(sf::RenderWindow& window, float x, float y) {
    sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(200, 200, 0)); // Yellow for path
    window.draw(shape);
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
        std::cout << "Error: An entry point already exists.\n";
        return;
    }
    if (grid[r][c] == nullptr || grid[r][c]->getCellType() != PATH) {
        std::cout << "Error: Entry must be placed on a PATH cell.\n";
        return;
    }
    entryX = r;
    entryY = c;
}

void gameMap::setExit(int r, int c) {
    if (exitX != -1 && exitY != -1) {
        std::cout << "Error: An exit point already exists.\n";
        return;
    }
    if (grid[r][c] == nullptr || grid[r][c]->getCellType() != PATH) {
        std::cout << "Error: Exit must be placed on a PATH cell.\n";
        return;
    }
    exitX = r;
    exitY = c;
}

void gameMap::displayMap(sf::RenderWindow& window) const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * CELL_SIZE;
            float y = i * CELL_SIZE;
            if (grid[i][j]) {
                grid[i][j]->display(window, x, y);
            }
            if (i == entryX && j == entryY) {
                sf::CircleShape entryMarker(CELL_SIZE / 3);
                entryMarker.setPosition(x + CELL_SIZE / 3, y + CELL_SIZE / 3);
                entryMarker.setFillColor(sf::Color::Green);
                window.draw(entryMarker);
            } else if (i == exitX && j == exitY) {
                sf::CircleShape exitMarker(CELL_SIZE / 3);
                exitMarker.setPosition(x + CELL_SIZE / 3, y + CELL_SIZE / 3);
                exitMarker.setFillColor(sf::Color::Red);
                window.draw(exitMarker);
            }
        }
    }
}

