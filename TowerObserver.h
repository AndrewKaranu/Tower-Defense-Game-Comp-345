#pragma once
#include "Observer.h"
#include "tower.h"

/**
 * @brief Observer that displays tower information when the tower changes.
 */
class TowerObserver : public Observer {
private:
    Tower* subject;
    
public:
    TowerObserver(Tower* t);
    ~TowerObserver();
    
    void update() override;
};