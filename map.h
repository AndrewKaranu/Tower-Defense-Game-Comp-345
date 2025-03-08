#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>
#include <map>
#include "critter.h"
#include "tower.h"

// Forward declarations
class Cell;
class pathCell;
class sceneryCell;

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
    /**
     * @brief Displays the cell.
     */
    virtual void display() = 0;
    /**
     * @brief Gets the type of the cell.
     * @return The cell type.
     */
    virtual cellType getCellType() = 0;
    /**
     * @brief Checks if a tower can be placed on the cell.
     * @return True if a tower can be placed, false otherwise.
     */
    virtual bool canPlaceTower() = 0;
    /**
     * @brief Checks if a critter can move on the cell.
     * @return True if a critter can move, false otherwise.
     */
    virtual bool canCritterMove() = 0;
    virtual ~Cell() = default;
};

/**
 * @brief Class representing a path cell in the game map.
 */
class pathCell : public Cell {
public:
    /**
     * @brief Displays the path cell.
     */
    void display() override;
    /**
     * @brief Gets the type of the cell.
     * @return The cell type.
     */
    cellType getCellType() override;
    /**
     * @brief Checks if a tower can be placed on the cell.
     * @return True if a tower can be placed, false otherwise.
     */
    bool canPlaceTower() override;
    /**
     * @brief Checks if a critter can move on the cell.
     * @return True if a critter can move, false otherwise.
     */
    bool canCritterMove() override;
};

/**
 * @brief Class representing a scenery cell in the game map.
 */
class sceneryCell : public Cell {
public:
    /**
     * @brief Displays the scenery cell.
     */
    void display() override;
    /**
     * @brief Gets the type of the cell.
     * @return The cell type.
     */
    cellType getCellType() override;
    /**
     * @brief Checks if a tower can be placed on the cell.
     * @return True if a tower can be placed, false otherwise.
     */
    bool canPlaceTower() override;
    /**
     * @brief Checks if a critter can move on the cell.
     * @return True if a critter can move, false otherwise.
     */
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
    // Store towers placed on the map
    std::vector<std::pair<int, int>> towerLocations;  // Store tower positions (row, col)
    std::map<std::pair<int, int>, Tower*> towers;     // Map positions to tower pointers

public:
    /**
     * @brief Constructor for the gameMap class.
     * @param r The number of rows in the map.
     * @param c The number of columns in the map.
     */
    gameMap(int r, int c);
    /**
     * @brief Destructor for the gameMap class.
     */
    ~gameMap();

    /**
     * @brief Sets a cell in the map.
     * @param r The row of the cell.
     * @param c The column of the cell.
     * @param cell The cell to set.
     */
    void setCell(int r, int c, Cell* cell);
    /**
     * @brief Sets the entry point of the map.
     * @param r The row of the entry point.
     * @param c The column of the entry point.
     */
    void setEntry(int r, int c);
    /**
     * @brief Removes the entry point of the map.
     */
    void removeEntry();
    /**
     * @brief Sets the exit point of the map.
     * @param r The row of the exit point.
     * @param c The column of the exit point.
     */
    void setExit(int r, int c);
    /**
     * @brief Removes the exit point of the map.
     */
    void removeExit();
    /**
     * @brief Checks if a critter can move to the given cell.
     * @param r The row of the cell.
     * @param c The column of the cell.
     * @return True if a critter can move, false otherwise.
     */
    bool canCritterMove(int r, int c) const;
    /**
     * @brief Checks if a tower can be placed on the given cell.
     * @param r The row of the cell.
     * @param c The column of the cell.
     * @return True if a tower can be placed, false otherwise.
     */
    bool canPlaceTower(int r, int c) const;
    /**
     * @brief Displays the map.
     */
    void displayMap() const;
    /**
     * @brief Displays the map with the critters on it.
     * @param critters The critters to display.
     */
    void displayMap(const std::vector<Critter*>& critters) const;
    /**
     * @brief Checks if the map is valid.
     * @return True if the map is valid, false otherwise.
     */
    bool isValidMap();

    // Add tower to map at specified location
    bool placeTower(int row, int col, Tower* tower);
    
    // Remove tower from map
    Tower* removeTower(int row, int col);
    
    // Get tower at a specific location (returns nullptr if no tower)
    Tower* getTowerAt(int row, int col) const;
    
    // Get all towers on the map
    std::vector<Tower*> getAllTowers() const;

    /**
     * @brief Gets the entry X coordinate.
     * @return The entry X coordinate.
     */
    int getEntryX() const { return entryX; }
    /**
     * @brief Gets the entry Y coordinate.
     * @return The entry Y coordinate.
     */
    int getEntryY() const { return entryY; }
    /**
     * @brief Gets the exit X coordinate.
     * @return The exit X coordinate.
     */
    int getExitX() const { return exitX; }
    /**
     * @brief Gets the exit Y coordinate.
     * @return The exit Y coordinate.
     */
    int getExitY() const { return exitY; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

#endif
