#include "base_tower.h"
#include "critter.h"

BasicTower::BasicTower() {
    levels = {
        {100, 70, 3.0f, 10.0f, 1.0f},   // Level 1
        {150, 105, 3.5f, 15.0f, 1.2f},  // Level 2
        {225, 157, 4.0f, 22.0f, 1.5f}   // Level 3
    };
}

void BasicTower::attack(std::vector<Critter*>& targets) {
    for(Critter* c : targets) {
        if(isInRange(0, 0, c->getX(), c->getY())) { // Assume tower position at (0,0)
            c->takeDamage(levels[currentLevel].power);
            break; 
        }
    }
}