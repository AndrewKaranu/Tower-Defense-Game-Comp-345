#pragma once
#include "tower.h"

class AoETower : public Tower {
public:
    AoETower();
    void attack(std::vector<Critter*>& targets) override;
};