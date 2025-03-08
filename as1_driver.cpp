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
    int numCrittersWave1 = 0;
    Critter* wave1 = generator.generateCritters(1, numCrittersWave1); // wave #1 example

    std::vector<Critter*> crittersWave1;
    for (int i = 0; i < numCrittersWave1; i++) {
        crittersWave1.push_back(&wave1[i]);
    }

    std::cout << "Created " << numCrittersWave1 << " critters for Wave 1.\n";
    for (Critter* c : crittersWave1) {
        std::cout << "Critter " << c->getId()
        << " HP: " << c->getHitpoints()
        << " Speed: " << c->getSpeed()
        << " Level: " << c->getLevel()
        << std::endl;
        // c->move(); // Show movement text
    }

    int numCrittersWave2 = 0;
    Critter* wave2 = generator.generateCritters(2, numCrittersWave2); // wave #2 example

    std::vector<Critter*> crittersWave2;
    for (int i = 0; i < numCrittersWave2; i++) {
        crittersWave2.push_back(&wave2[i]);
    }

    std::cout << "Created " << numCrittersWave2 << " critters for Wave 2.\n";
    for (Critter* c : crittersWave2) {
        std::cout << "Critter " << c->getId()
        << " HP: " << c->getHitpoints()
        << " Speed: " << c->getSpeed()
        << " Level: " << c->getLevel()
        << std::endl;
        // c->move(); // Show movement text
    }

    delete[] wave1;
    delete[] wave2;
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
 * @brief Demonstrates critter and map interaction.
 */
void demoCritterMapInteraction() {
    std::cout << "\n--- Critter and Map Interaction Demonstration ---\n";

    // Create a sample map (you can customize this)
    gameMap myMap(5, 5);
    myMap.setCell(0, 0, new pathCell());
    myMap.setCell(0, 1, new pathCell());
    myMap.setCell(0, 2, new pathCell());
    myMap.setCell(0, 3, new pathCell());
    myMap.setCell(0, 4, new pathCell());
    myMap.setCell(1, 0, new pathCell());
    myMap.setCell(1, 1, new sceneryCell());
    myMap.setCell(1, 2, new pathCell());
    myMap.setCell(1, 3, new sceneryCell());
    myMap.setCell(1, 4, new pathCell());
    myMap.setCell(2, 0, new pathCell());
    myMap.setCell(2, 1, new sceneryCell());
    myMap.setCell(2, 2, new pathCell());
    myMap.setCell(2, 3, new pathCell());
    myMap.setCell(2, 4, new sceneryCell());
    myMap.setCell(3, 0, new pathCell());
    myMap.setCell(3, 1, new sceneryCell());
    myMap.setCell(3, 2, new pathCell());
    myMap.setCell(3, 3, new pathCell());
    myMap.setCell(3, 4, new pathCell());
    myMap.setCell(4, 0, new sceneryCell());
    myMap.setCell(4, 1, new sceneryCell());
    myMap.setCell(4, 2, new sceneryCell());
    myMap.setCell(4, 3, new sceneryCell());
    myMap.setCell(4, 4, new pathCell());
    myMap.setEntry(0, 0);
    myMap.setExit(4, 4);

    // Generate a single critter at the entry point
    CritterGroupGenerator generator;
    int numCritters = 0;
    Critter* critter = generator.generateCritters(1, numCritters, myMap.getEntryX(), myMap.getEntryY());

    if (critter == nullptr) {
        std::cout << "Failed to generate critter.\n";
        return;
    }

    std::cout << "Initial map:\n";
    std::vector<Critter*> critters;
    critters.push_back(critter);
    myMap.displayMap(critters);

    // Simulate critter movement
    int steps = 10;
    bool reachedExit = false; // Flag to track if the critter reached the exit
    for (int i = 0; i < steps; ++i) {
        std::cout << "\nAfter step " << i + 1 << ":\n";
        if (critter->isAlive() && !reachedExit) {
            critter->move(myMap);

            // Check if the critter has reached the exit
            if (critter->getX() == myMap.getExitX() && critter->getY() == myMap.getExitY()) {
                std::cout << "Critter " << critter->getId() << " has reached the exit!\n";
                reachedExit = true;
            }
        } else if (!critter->isAlive()) {
            std::cout << "Critter " << critter->getId() << " is dead!\n";
            break;
        } else {
            // Critter already reached the exit, no need to move it further
            std::cout << "Critter " << critter->getId() << " is at the exit.\n";
        }
        myMap.displayMap(critters);
    }

    delete critter;
}

/**
 * @brief Demonstrates tower placement on the map.
 */
void demoTowerPlacement() {
    std::cout << "\n--- Tower Placement Demonstration ---\n";
    
    // Create a sample map
    gameMap myMap(5, 5);
    
    // Set up a path and scenery cells (same map as in other demos)
    myMap.setCell(0, 0, new pathCell());
    myMap.setCell(0, 1, new pathCell());
    myMap.setCell(0, 2, new pathCell());
    myMap.setCell(0, 3, new pathCell());
    myMap.setCell(0, 4, new sceneryCell());
    myMap.setCell(1, 0, new pathCell());
    myMap.setCell(1, 1, new sceneryCell());
    myMap.setCell(1, 2, new pathCell());
    myMap.setCell(1, 3, new sceneryCell());
    myMap.setCell(1, 4, new pathCell());
    myMap.setCell(2, 0, new pathCell());
    myMap.setCell(2, 1, new sceneryCell());
    myMap.setCell(2, 2, new pathCell());
    myMap.setCell(2, 3, new pathCell());
    myMap.setCell(2, 4, new sceneryCell());
    myMap.setCell(3, 0, new pathCell());
    myMap.setCell(3, 1, new sceneryCell());
    myMap.setCell(3, 2, new pathCell());
    myMap.setCell(3, 3, new pathCell());
    myMap.setCell(3, 4, new pathCell());
    myMap.setCell(4, 0, new sceneryCell());
    myMap.setCell(4, 1, new sceneryCell());
    myMap.setCell(4, 2, new sceneryCell());
    myMap.setCell(4, 3, new sceneryCell());
    myMap.setCell(4, 4, new pathCell());
    
    // Set entry and exit points
    myMap.setEntry(0, 0);
    myMap.setExit(4, 4);
    
    std::cout << "\nInitial Map:\n";
    myMap.displayMap();
    
    // Try to place towers on different cells
    std::cout << "\nPlacing towers on map...\n";
    
    // Create different tower types
    BasicTower* basic1 = new BasicTower();
    BasicTower* basic2 = new BasicTower();
    SlowTower* slow1 = new SlowTower();
    AoETower* aoe1 = new AoETower();
    
    // Try valid placements (on scenery cells)
    std::cout << "Placing Basic Tower at (0,4): " 
              << (myMap.placeTower(0, 4, basic1) ? "SUCCESS" : "FAILURE") << std::endl;
    
    std::cout << "Placing Slow Tower at (1,1): " 
              << (myMap.placeTower(1, 1, slow1) ? "SUCCESS" : "FAILURE") << std::endl;
    
    std::cout << "Placing AoE Tower at (2,1): " 
              << (myMap.placeTower(2, 1, aoe1) ? "SUCCESS" : "FAILURE") << std::endl;
    
    // Try invalid placements (on path cells)
    std::cout << "Placing Basic Tower at (0,1) (path cell): " 
              << (myMap.placeTower(0, 1, basic2) ? "SUCCESS" : "FAILURE") << std::endl;
    
    // Display map with towers
    std::cout << "\nMap with towers (B=Basic Tower, S=Slow Tower, A=AoE Tower):\n";
    myMap.displayMap();
    
    // Test tower removal
    std::cout << "\nRemoving tower at (1,1)...\n";
    Tower* removed = myMap.removeTower(1, 1);
    if (removed) {
        std::cout << "Tower successfully removed.\n";
        delete removed;  // Clean up the removed tower
    } else {
        std::cout << "No tower found at that location.\n";
    }
    
    // Try removing from an empty cell
    std::cout << "Removing tower from empty cell (3,3)...\n";
    removed = myMap.removeTower(3, 3);
    if (removed) {
        std::cout << "Tower successfully removed.\n";
        delete removed;
    } else {
        std::cout << "No tower found at that location.\n";
    }
    
    // Display final map
    std::cout << "\nFinal map after tower removal:\n";
    myMap.displayMap();
    
    // Add critters and show both towers and critters
    std::cout << "\nAdding critters to show on map with towers:\n";
    CritterGroupGenerator generator;
    int numCritters = 0;
    Critter* critter = generator.generateCritters(1, numCritters, myMap.getEntryX(), myMap.getEntryY());
    if (critter) {
        std::vector<Critter*> critters;
        critters.push_back(critter);
        myMap.displayMap(critters);
        
        // Test tower attacks on the critters
        std::cout << "\nTesting tower attacks on critters...\n";
        std::cout << "Critter initial HP: " << critter->getHitpoints() << std::endl;
        
        // Get all towers and let them attack
        std::vector<Tower*> towers = myMap.getAllTowers();
        std::cout << "Number of towers on map: " << towers.size() << std::endl;
        
        for (Tower* tower : towers) {
            tower->attack(critters);
        }
        
        std::cout << "Critter HP after tower attacks: " << critter->getHitpoints() << std::endl;
        delete critter;
    }
    
    // Clean up any remaining towers
    for (int i = 0; i < myMap.getRows(); ++i) {
        for (int j = 0; j < myMap.getCols(); ++j) {
            Tower* tower = myMap.removeTower(i, j);
            if (tower) {
                delete tower;
            }
        }
    }
}

/**
 * @brief Main function with a simple menu to demonstrate maps, critters, and towers separately.
 */
/**
 * @brief Main function with a simple menu to demonstrate maps, critters, and towers separately.
 */
int main() {
    while (true) {
        std::cout
            << "\n      === WELCOME TO ===\n"
            << "\n=== Tower Defense Game Test ===\n"
            << "\n=== Main Menu ===\n"
            << "1) Demonstrate Maps Generation\n"
            << "2) Demonstrate Critters Generation\n"
            << "3) Demonstrate Towers and Critters Interactions\n"
            << "4) Demonstrate Critter and Map Interaction\n"
            << "5) Demonstrate Tower Placement on Map\n"  // New option
            << "6) Exit\n"  // Updated exit option number
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
            demoCritterMapInteraction();
            break;
        case 5:
            demoTowerPlacement();  // Call the new function
            break;
        case 6:  // Updated exit case number
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
