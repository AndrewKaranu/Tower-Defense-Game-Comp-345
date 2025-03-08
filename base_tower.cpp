#include "base_tower.h"
#include "critter.h"
#include <vector> 
#include <iostream>

/**
 * @brief Constructor for the BasicTower class.
 *
 * Initializes the levels vector with the statistics for each level.
 */
BasicTower::BasicTower() {
    levels = {
        {100, 70, 3.0f, 10.0f, 1.0f},   // Level 1
        {150, 105, 3.5f, 15.0f, 1.2f},  // Level 2
        {225, 157, 4.0f, 22.0f, 1.5f}   // Level 3
    };
}

/**
 * @brief Attacks a vector of critters.
 *
 * The tower attacks the first critter within its range.
 *
 * @param targets A vector of pointers to Critter objects that can be attacked.
 */
void BasicTower::attack(std::vector<Critter*>& targets) {
    // Basic tower only hits the first target in range
    if (!targets.empty()) {  // Now this should work
        Critter* target = targets[0];
        target->takeDamage(levels[currentLevel].power);
        
        // Debug output
        std::cout << "BasicTower hit critter #" << target->getId() 
                  << " for " << levels[currentLevel].power << " damage" << std::endl;
    }
}
