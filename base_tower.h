#pragma once
#include "tower.h"

class BasicTower : public Tower {
public:
    BasicTower();
    void attack(std::vector<Critter*>& targets) override;
};