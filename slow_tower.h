#pragma once
#include "tower.h"
#include "critter.h"

class SlowTower : public Tower {
public:
    SlowTower();
    void attack(std::vector<Critter*>& targets) override;
    
private:
    float slowPercentage = 0.3f; // 30% slower movemnet
    void applySlow(Critter* critter);
};