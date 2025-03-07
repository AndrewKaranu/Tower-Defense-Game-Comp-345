#include "mapObserver.h"
#include "map.h"

MapObserver::MapObserver(Map& m) : map(m) {
    map.addObserver(this);
}

MapObserver::~MapObserver() {
    map.removeObserver(this);
}

void MapObserver::update() {
    std::cout << "Map Updated:\n";
    map.display();
}



