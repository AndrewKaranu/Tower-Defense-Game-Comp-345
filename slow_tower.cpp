#include "slow_tower.h"
#include "critter.h"

SlowTower::SlowTower() {
    levels = {
        {120, 84, 2.8f, 5.0f, 0.5f},   // Level 1
        {180, 126, 3.3f, 7.5f, 0.6f}, // Level 2
        {270, 189, 4.0f, 11.0f, 0.7f} // Level 3
    };
}

void SlowTower::attack(std::vector<Critter*>& targets) {
    for(Critter* c : targets) {
        if(isInRange(0, 0, c->getX(), c->getY())) {
            c->takeDamage(levels[currentLevel].power);
            applySlow(c);
        }
    }
}

void SlowTower::applySlow(Critter* critter) {
    double newSpeed = critter->getSpeed() * (1.0f - slowPercentage);
    critter->setSpeed(newSpeed);
}