#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include "observer.h"
#include "map.h"
#include <iostream>


class MapObserver : public Observer {
private:
    Map& map; // Map being observed

public:
    MapObserver(Map& m);
    ~MapObserver();
    void update() override;
};

#endif

