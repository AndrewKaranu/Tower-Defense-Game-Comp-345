#include "aoe_tower.h"
#include "critter.h"


AoETower::AoETower() {
    levels = {
        {150, 105, 2.5f, 8.0f, 0.8f},  // Level 1
        {225, 157, 3.0f, 12.0f, 1.0f}, // Level 2
        {337, 235, 3.5f, 18.0f, 1.2f}  // Level 3
    };
}

void AoETower::attack(std::vector<Critter*>& targets) {
    for(Critter* c : targets) {
        if(isInRange(0, 0, c->getX(), c->getY())) {
            c->takeDamage(levels[currentLevel].power * 0.6f); // 60% of the power we can change this later
        }
    }
}