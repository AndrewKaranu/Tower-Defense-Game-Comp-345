#include "mapObserver.h"

// ConsoleMapObserver Implementation

ConsoleMapObserver::ConsoleMapObserver(const gameMap* map) : MapObserver(map) {}

void ConsoleMapObserver::update() {
    // Assuming gameMap has a method displayMap to show the map
    std::cout << "Displaying map:\n";
    map->displayMap();  // Display the updated map in the console
}
