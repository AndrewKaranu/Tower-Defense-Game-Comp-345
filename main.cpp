#include "slow_tower.h"
#include "base_tower.h"
#include "aoe_tower.h"
#include "critter.h"
#include <vector>
#include <iostream>

void testTower(Tower& tower, std::vector<Critter*>& critters) {
    std::cout << "Initial attack:" << std::endl;
    tower.attack(critters);
    for (Critter* c : critters) {
        std::cout << "Critter " << c->getId() << " hitpoints: " << c->getHitpoints() << ", speed: " << c->getSpeed() << std::endl;
    }

    std::cout << "Upgrading tower..." << std::endl;
    if (tower.upgrade()) {
        std::cout << "Tower upgraded to level " << tower.getLevel() << std::endl;
    } else {
        std::cout << "Tower upgrade failed" << std::endl;
    }

    std::cout << "Attack after upgrade:" << std::endl;
    tower.attack(critters);
    for (Critter* c : critters) {
        std::cout << "Critter " << c->getId() << " hitpoints: " << c->getHitpoints() << ", speed: " << c->getSpeed() << std::endl;
    }

    std::cout << "Selling tower for " << tower.sell() << " currency" << std::endl;
}

int main() {
    // Create some critters
    Critter critter1(1, 100, 10, 5, 1.0, 1);
    Critter critter2(2, 150, 15, 7, 1.2, 1);
    Critter critter3(3, 200, 20, 10, 1.5, 1);

    std::vector<Critter*> critters = { &critter1, &critter2, &critter3 };

    // Create towers
    SlowTower slowTower;
    BasicTower basicTower;
    AoETower aoeTower;

    // Test SlowTower
    std::cout << "Testing SlowTower:" << std::endl;
    testTower(slowTower, critters);

    // Reset critters for next test
    critter1.setHitpoints(100);
    critter1.setSpeed(1.0);
    critter2.setHitpoints(150);
    critter2.setSpeed(1.2);
    critter3.setHitpoints(200);
    critter3.setSpeed(1.5);

    // Test BasicTower
    std::cout << "Testing BasicTower:" << std::endl;
    testTower(basicTower, critters);

    // Reset critters for next test
    critter1.setHitpoints(100);
    critter2.setHitpoints(150);
    critter3.setHitpoints(200);

    // Test AoETower
    std::cout << "Testing AoETower:" << std::endl;
    testTower(aoeTower, critters);

    return 0;
}