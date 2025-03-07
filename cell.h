#ifndef CELL_H
#define CELL_H

#include <string>
using namespace std;

class Cell {
protected:
    int x, y;  // Coordinates of the cell
    bool canPlaceTower;   // Whether a tower can be placed on this cell
    bool canPlaceCritter; // Whether a critter can be placed on this cell

public:
    Cell(int x, int y, bool canTower = false, bool canCritter = false);
    virtual bool canPlaceTowerHere() const;
    virtual bool canPlaceCritterHere() const;
    virtual string getCellType() const = 0;  // Return cell type as a string

    int getX() const;
    int getY() const;

    virtual ~Cell();
};

class SceneryCell : public Cell {
public:
    SceneryCell(int x, int y);
    bool canPlaceTowerHere() const override;
    bool canPlaceCritterHere() const override;
    std::string getCellType() const override;  // Return "Scenery"
};

class PathCell : public Cell {
public:
    PathCell(int x, int y);
    bool canPlaceTowerHere() const override;
    bool canPlaceCritterHere() const override;
    std::string getCellType() const override;  // Return "Path"
};

#endif // CELL_H
