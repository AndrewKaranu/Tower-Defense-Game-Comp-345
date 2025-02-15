#include "slow_tower.h"
#include "base_tower.h"
#include "aoe_tower.h"
#include "critter.h"
#include "CritterGroupGenerator.h"
#include <vector>
#include <iostream>

/**
 * @brief Tests the functionality of a tower.
 * 
 * This function tests the attack, upgrade, and sell functionalities of a tower.
 * It prints the results of each action to the console.
 * 
 * @param tower The tower to be tested.
 * @param critters A vector of pointers to critters that the tower will attack.
 */
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

/**
 * @brief The main function of the program.
 * 
 * This function creates some critters and towers, and tests the towers using the testTower function.
 * 
 * @return int Returns 0 upon successful execution.
 */
int main() {
    CritterGroupGenerator generator;

    // Generate critters for wave 1
    int numCrittersWave1;
    Critter* wave1 = generator.generateCritters(1, numCrittersWave1);
    std::vector<Critter*> crittersWave1;
    for (int i = 0; i < numCrittersWave1; ++i) {
        crittersWave1.push_back(&wave1[i]);
    }

    // Create towers
    SlowTower slowTower;
    BasicTower basicTower;
    AoETower aoeTower;

    // Test SlowTower
    std::cout << "Testing SlowTower:" << std::endl;
    testTower(slowTower, crittersWave1);

    // Reset critters for next test
    for (Critter* critter : crittersWave1) {
        critter->setHitpoints(100);
        critter->setSpeed(1.0);
    }

    // Test BasicTower
    std::cout << "Testing BasicTower:" << std::endl;
    testTower(basicTower, crittersWave1);

    // Reset critters for next test
    for (Critter* critter : crittersWave1) {
        critter->setHitpoints(100);
    }

    // Test AoETower
    std::cout << "Testing AoETower:" << std::endl;
    testTower(aoeTower, crittersWave1);

    // Clean up dynamically allocated memory
    delete[] wave1;

    return 0;
}