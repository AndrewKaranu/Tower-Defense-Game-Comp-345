#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>

// Forward declarations
class Cell;
class pathCell;
class sceneryCell;

enum cellType {
    SCENERY,
    PATH
};

class Cell {
public:
    virtual void display() = 0;
    virtual cellType getCellType() = 0;
    virtual bool canPlaceTower() = 0;
    virtual bool canCritterMove() = 0;
    virtual ~Cell() = default;
};

class pathCell : public Cell {
public:
    void display() override;
    cellType getCellType() override;
    bool canPlaceTower() override;
    bool canCritterMove() override;
};

class sceneryCell : public Cell {
public:
    void display() override;
    cellType getCellType() override;
    bool canPlaceTower() override;
    bool canCritterMove() override;
};

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
    void displayMap() const;
    bool isValidMap();
};

#endif