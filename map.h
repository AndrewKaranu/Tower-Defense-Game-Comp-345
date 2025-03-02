#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "critter.h"

// Forward declarations
class Cell;
class pathCell;
class sceneryCell;

const int CELL_SIZE = 40; // Size of each cell in pixels

/**
 * @brief Enum representing the type of a cell.
 */
enum cellType {
    SCENERY,
    PATH
};

/**
 * @brief Abstract class representing a cell in the game map.
 */
class Cell {
public:
    virtual void display(sf::RenderWindow& window, int x, int y) = 0; // Now takes SFML window & position
    virtual cellType getCellType() = 0;
    virtual bool canPlaceTower() = 0;
    virtual bool canCritterMove() = 0;
    virtual ~Cell() = default;
};

/**
 * @brief Class representing a path cell in the game map.
 */
class pathCell : public Cell {
public:
    void display(sf::RenderWindow& window, int x, int y) override;
    cellType getCellType() override;
    bool canPlaceTower() override;
    bool canCritterMove() override;
};

/**
 * @brief Class representing a scenery cell in the game map.
 */
class sceneryCell : public Cell {
public:
    void display(sf::RenderWindow& window, int x, int y) override;
    cellType getCellType() override;
    bool canPlaceTower() override;
    bool canCritterMove() override;
};

/**
 * @brief Class representing the game map.
 */
class gameMap {
private:
    std::vector<std::vector<Cell*>> grid;
    int rows, cols;
    int entryX = -1, entryY = -1;
    int exitX = -1, exitY = -1;
    bool isPathConnected(int x, int y, std::vector<std::vector<bool>>& visited);

public:
    gameMap(int r, int c);
    ~gameMap();
    
    void setCell(int r, int c, Cell* cell);
    void setEntry(int r, int c);
    void removeEntry();
    void setExit(int r, int c);
    void removeExit();
    bool canCritterMove(int r, int c) const;
    bool canPlaceTower(int r, int c) const;
    
    // GUI-compatible display function
    void displayMap(sf::RenderWindow& window) const;

    void displayMap(sf::RenderWindow& window, const std::vector<Critter*>& critters) const;
    
    bool isValidMap();

    int getEntryX() const { return entryX; }
    int getEntryY() const { return entryY; }
    int getExitX() const { return exitX; }
    int getExitY() const { return exitY; }
};

#endif
