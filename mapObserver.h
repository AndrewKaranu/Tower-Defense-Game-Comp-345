#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include <iostream>
#include "map.h"  

// Abstract Observer class
class Observer {
public:
    virtual void update() = 0;  // Pure virtual method for updates
    virtual ~Observer() = default;  // Virtual destructor
};


class MapObserver : public Observer {
protected:
    const gameMap* map;  // Reference to the gameMap to observe
public:
    MapObserver(const gameMap* map) : map(map) {}
    virtual void update() override = 0;  // Pure virtual update method
};

// Concrete Observer to display the gameMap in the console
class ConsoleMapObserver : public MapObserver {
public:
    ConsoleMapObserver(const gameMap* map);
    void update() override;  // Method to update and display the map
};

#endif
