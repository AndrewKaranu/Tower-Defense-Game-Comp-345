#include "aoe_tower.h"
#include "critter.h"
#include <vector>  // Add this include
#include <iostream>  // Add this include

/**
 * @brief Constructor for the AoETower class.
 *
 * Initializes the levels vector with the statistics for each level.
 */
AoETower::AoETower() {
    levels = {
        {200, 35, 2.5f, 5.0f, 1.0f},   // Level 1
        {300, 52, 3.0f, 7.5f, 1.2f},   // Level 2
        {450, 78, 3.5f, 11.0f, 1.5f}  // Level 3
    };
}

void AoETower::attack(std::vector<Critter*>& targets) {
    // AoE tower hits all targets in range
    for (Critter* target : targets) {  // This should work now
        target->takeDamage(levels[currentLevel].power);
        
        // Debug output
        std::cout << "AoETower hit critter #" << target->getId() 
                  << " for " << levels[currentLevel].power << " damage" << std::endl;
    }
}