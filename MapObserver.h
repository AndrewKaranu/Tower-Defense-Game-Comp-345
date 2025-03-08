#pragma once
#include "Observer.h"
#include "map.h"
#include <QWidget>

class Tower;
class BasicTower;
class SlowTower;
class AoETower;

/**
 * @brief Observer that displays map information when the map changes.
 */
class MapObserver : public Observer, public QWidget {
    Q_OBJECT
    
private:
    gameMap* subject;
    
public:
    MapObserver(gameMap* m, QWidget* parent = nullptr);
    ~MapObserver();
    
    void update() override;
    
protected:
    void paintEvent(QPaintEvent* event) override;
};