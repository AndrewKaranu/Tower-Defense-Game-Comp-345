#include "slow_tower.h"
#include "base_tower.h"
#include "aoe_tower.h"
#include "critter.h"
#include "CritterGroupGenerator.h"
#include "map.h"
#include <vector>
#include <iostream>

/**
 * @brief Tests the functionality of a tower (existing code).
 */
void testTower(Tower& tower, std::vector<Critter*>& critters) {
    // ...existing code...
    std::cout << "Initial attack:" << std::endl;
    tower.attack(critters);
    for (Critter* c : critters) {
        std::cout << "Critter " << c->getId() 
                  << " hitpoints: " << c->getHitpoints() 
                  << ", speed: " << c->getSpeed() 
                  << std::endl;
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
        std::cout << "Critter " << c->getId() 
                  << " hitpoints: " << c->getHitpoints() 
                  << ", speed: " << c->getSpeed() 
                  << std::endl;
    }

    std::cout << "Selling tower for " << tower.sell() << " currency" << std::endl;
}

/**
 * @brief Demonstrates a valid 5x5 map and checks critter/tower placement.
 */
void checkValidMap() {
    std::cout << "\n--- Valid Map Demonstration ---\n";
    std::cout << "Creating My Map 1 (5x5)\n";
    gameMap myMap1(5, 5);

    // Set up a path and scenery cells
    myMap1.setCell(0, 0, new pathCell());
    myMap1.setCell(0, 1, new pathCell());
    myMap1.setCell(0, 2, new pathCell());
    myMap1.setCell(0, 3, new pathCell());
    myMap1.setCell(0, 4, new sceneryCell());
    myMap1.setCell(1, 0, new pathCell());
    myMap1.setCell(1, 1, new sceneryCell());
    myMap1.setCell(1, 2, new pathCell());
    myMap1.setCell(1, 3, new sceneryCell());
    myMap1.setCell(1, 4, new pathCell());
    myMap1.setCell(2, 0, new pathCell());
    myMap1.setCell(2, 1, new sceneryCell());
    myMap1.setCell(2, 2, new pathCell());
    myMap1.setCell(2, 3, new pathCell());
    myMap1.setCell(2, 4, new sceneryCell());
    myMap1.setCell(3, 0, new pathCell());
    myMap1.setCell(3, 1, new sceneryCell());
    myMap1.setCell(3, 2, new pathCell());
    myMap1.setCell(3, 3, new pathCell());
    myMap1.setCell(3, 4, new pathCell());
    myMap1.setCell(4, 0, new sceneryCell());
    myMap1.setCell(4, 1, new sceneryCell());
    myMap1.setCell(4, 2, new sceneryCell());
    myMap1.setCell(4, 3, new sceneryCell());
    myMap1.setCell(4, 4, new pathCell());

    // Set entry and exit points
    myMap1.setEntry(0, 0);
    myMap1.setExit(4, 4);

    std::cout << "\nDisplaying Game Map 1:\n";
    myMap1.displayMap();

    // Check map validity
    if (myMap1.isValidMap()) {
        std::cout << "\nThe map is valid!\n";
    } else {
        std::cout << "\nThe map is invalid!\n";
    }

    // Checking movement and tower placement
    std::cout << "\nCritter movement check:\n";
    std::cout << "(0,0) Path => " 
              << (myMap1.canCritterMove(0, 0) ? "YES" : "NO") 
              << std::endl;
    std::cout << "(1,1) Scenery => " 
              << (myMap1.canCritterMove(1, 1) ? "YES" : "NO") 
              << std::endl;

    std::cout << "\nTower placement check:\n";
    std::cout << "(0,1) Path => " 
              << (myMap1.canPlaceTower(0, 1) ? "YES" : "NO") 
              << std::endl;
    std::cout << "(1,1) Scenery => " 
              << (myMap1.canPlaceTower(1, 1) ? "YES" : "NO") 
              << std::endl;
}

/**
 * @brief Demonstrates an invalid 4x3 map (no entry/exit) and shows error messages.
 */
void checkInvalidMaps() {
    std::cout << "\n--- Invalid Map Demonstration ---\n";
    std::cout << "Creating myMap2 (4x3) with no entry or exit.\n";
    gameMap myMap2(4, 3);

    // Some path/scenery cells but no entry/exit
    myMap2.setCell(0, 0, new pathCell());
    myMap2.setCell(0, 1, new pathCell());
    myMap2.setCell(0, 2, new sceneryCell());
    myMap2.setCell(1, 0, new sceneryCell());
    myMap2.setCell(1, 1, new pathCell());
    myMap2.setCell(1, 2, new sceneryCell());
    myMap2.setCell(2, 0, new sceneryCell());
    myMap2.setCell(2, 1, new pathCell());
    myMap2.setCell(2, 2, new pathCell());
    myMap2.setCell(3, 0, new pathCell());
    myMap2.setCell(3, 1, new sceneryCell());
    myMap2.setCell(3, 2, new pathCell());

    myMap2.displayMap();

    if (myMap2.isValidMap()) {
        std::cout << "\nMap2 is valid (should not happen)!\n";
    } else {
        std::cout << "\nMap2 is invalid (no entry or exit).\n";
    }

    // Showcase error messages when trying to add multiple entry/exit
    std::cout << "\nAdding multiple entry/exit points:\n";
    myMap2.setEntry(0, 0);
    myMap2.setEntry(0, 2);
    myMap2.removeEntry();
    myMap2.setEntry(0, 2);
    myMap2.setExit(3, 2);
    myMap2.setExit(3, 1);
    myMap2.removeExit();
    myMap2.setExit(3, 1);
}

/**
 * @brief Demonstrates a disconnected 4x4 map (invalid path).
 */
void checkDisconnectedMap() {
    std::cout << "\n--- Disconnected Map Demonstration ---\n";
    gameMap myMap3(4, 4);

    // Create a path that doesn't connect properly
    myMap3.setCell(0, 0, new pathCell());
    myMap3.setCell(0, 1, new pathCell());
    myMap3.setCell(0, 2, new pathCell());
    myMap3.setCell(0, 3, new pathCell());
    myMap3.setCell(1, 0, new pathCell());
    myMap3.setCell(1, 1, new sceneryCell());
    myMap3.setCell(1, 2, new pathCell());
    myMap3.setCell(1, 3, new sceneryCell());
    myMap3.setCell(2, 0, new pathCell());
    myMap3.setCell(2, 1, new sceneryCell());
    myMap3.setCell(2, 2, new pathCell());
    myMap3.setCell(2, 3, new sceneryCell());
    myMap3.setCell(3, 0, new pathCell());
    myMap3.setCell(3, 1, new sceneryCell());
    // (3,2) is scenery
    myMap3.setCell(3, 3, new pathCell());

    // Entry/exit
    myMap3.setEntry(0, 0);
    myMap3.setExit(3, 3);

    std::cout << "Displaying myMap3 (disconnected paths):\n";
    myMap3.displayMap();

    if (myMap3.isValidMap()) {
        std::cout << "Map3 is wrongly valid (paths are disconnected)!\n";
    } else {
        std::cout << "Map3 is invalid (disconnected path), as expected.\n";
    }

    std::cout << "\nCreating myMap4 (4x6) empty map:\n";
    gameMap myMap4(4, 6);
    myMap4.displayMap();
}

/**
 * @brief Demonstrates all map checks in one place.
 */
void demoMaps() {
    checkValidMap();
    checkInvalidMaps();
    checkDisconnectedMap();
}

/**
 * @brief Demonstrates basic critter usage:
 *        - generating a wave,
 *        - showing movement,
 *        - printing stats.
 */
void demoCritters() {
    std::cout << "\n--- Critter Demonstration ---\n";

    CritterGroupGenerator generator;
    int numCritters = 0;
    Critter* wave = generator.generateCritters(1, numCritters); // wave #1 example
    Critter* wave = generator.generateCritters(2, numCritters); // wave #2 example

    
    

    std::vector<Critter*> critters;
    for(int i = 0; i < numCritters; i++) {
        critters.push_back(&wave[i]);
    }

    std::cout << "Created " << numCritters << " critters.\n";
    for(Critter* c : critters) {
        std::cout << "Critter " << c->getId() 
                  << " HP: " << c->getHitpoints()
                  << " Speed: " << c->getSpeed()
                  << " Level: " << c->getLevel()
                  << std::endl;
        c->move(); // Show movement text
    }

    delete[] wave;
}

/**
 * @brief Demonstrates testing towers with a fresh set of critters.
 */
void demoTowers() {
    std::cout << "\n--- Tower Demonstration ---\n";

    // Generate some critters for testing
    CritterGroupGenerator generator;
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

    // Test each separately
    std::cout << "Testing SlowTower:\n";
    testTower(slowTower, crittersWave1);

    // Reset critters
    for (Critter* c : crittersWave1) {
        c->setHitpoints(100);
        c->setSpeed(1.0);
    }

    std::cout << "\nTesting BasicTower:\n";
    testTower(basicTower, crittersWave1);

    // Reset critters
    for (Critter* c : crittersWave1) {
        c->setHitpoints(100);
    }

    std::cout << "\nTesting AoETower:\n";
    testTower(aoeTower, crittersWave1);

    delete[] wave1;
}

/**
 * @brief Main function with a simple menu to demonstrate maps, critters, and towers separately.
 */
int main() {
    while (true) {
        std::cout 
            << "\n=== Main Menu ===\n"
            << "1) Demonstrate Maps\n"
            << "2) Demonstrate Critters\n"
            << "3) Demonstrate Towers\n"
            << "4) Exit\n"
            << "Choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                demoMaps();
                break;
            case 2:
                demoCritters();
                break;
            case 3:
                demoTowers();
                break;
            case 4:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}