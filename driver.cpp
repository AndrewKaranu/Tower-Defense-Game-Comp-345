#include <iostream>
#include "map.h"

int main() {
    
    // Create a 5x5 game map
    gameMap myMap(5, 5);

    // Set up a valid path (manually placing path cells)
    myMap.setCell(0, 0, new pathCell());
    myMap.setCell(0, 1, new pathCell());
    myMap.setCell(0, 2, new pathCell());
    myMap.setCell(0, 3, new pathCell());
    myMap.setCell(0, 4, new sceneryCell());

    myMap.setCell(1, 0, new pathCell());
    myMap.setCell(1, 1, new sceneryCell());
    myMap.setCell(1, 2, new pathCell());
    myMap.setCell(1, 3, new sceneryCell());
    myMap.setCell(1, 4, new pathCell());

    myMap.setCell(2, 0, new pathCell());
    myMap.setCell(2, 1, new sceneryCell());
    myMap.setCell(2, 2, new pathCell());
    myMap.setCell(2, 3, new pathCell());
    myMap.setCell(2, 4, new sceneryCell());

    myMap.setCell(3, 0, new pathCell());
    myMap.setCell(3, 1, new sceneryCell());
    myMap.setCell(3, 2, new pathCell());
    myMap.setCell(3, 3, new pathCell());
    myMap.setCell(3, 4, new pathCell());

    myMap.setCell(4, 0, new sceneryCell());
    myMap.setCell(4, 1, new sceneryCell());
    myMap.setCell(4, 2, new sceneryCell());
    myMap.setCell(4, 3, new sceneryCell());
    myMap.setCell(4, 4, new pathCell());

    // Set entry and exit points
    myMap.setEntry(0, 0);
    myMap.setExit(4, 4);

    // Display the map
    std::cout << "Game Map:\n";
    myMap.displayMap();

    // Check map validity
    if (myMap.isValidMap()) {
        std::cout << "The map is valid!\n";
    } else {
        std::cout << "The map is invalid!\n";
    }

    return 0;
}
