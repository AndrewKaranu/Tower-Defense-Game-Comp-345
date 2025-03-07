#include "cell.h"

// Base class constructor
Cell::Cell(int x, int y, bool canTower, bool canCritter)
    : x(x), y(y), canPlaceTower(canTower), canPlaceCritter(canCritter) {}

bool Cell::canPlaceTowerHere() const {
    return canPlaceTower;
}

bool Cell::canPlaceCritterHere() const {
    return canPlaceCritter;
}

int Cell::getX() const {
    return x;
}

int Cell::getY() const {
    return y;
}

Cell::~Cell() {}

// SceneryCell constructor
SceneryCell::SceneryCell(int x, int y)
    : Cell(x, y, false, false) {}


bool SceneryCell::canPlaceTowerHere() const {
    return false;  // Cannot place tower on scenery
}

bool SceneryCell::canPlaceCritterHere() const {
    return false;  // Cannot place critter on scenery`
}

std::string SceneryCell::getCellType() const {
    return "Scenery";
}

// PathCell constructor
PathCell::PathCell(int x, int y)
    : Cell(x, y, true, true) {}

bool PathCell::canPlaceTowerHere() const {
    return true;  // Can place tower on path
}

bool PathCell::canPlaceCritterHere() const {
    return true;  // Can place critter on path
}

std::string PathCell::getCellType() const {
    return "Path";
}
