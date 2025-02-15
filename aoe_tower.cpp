#include "aoe_tower.h"
#include "critter.h"

/**
 * @brief Constructor for the AoETower class.
 * 
 * Initializes the levels vector with the statistics for each level.
 */
AoETower::AoETower() {
    levels = {
        {150, 105, 2.5f, 8.0f, 0.8f},  // Level 1
        {225, 157, 3.0f, 12.0f, 1.0f}, // Level 2
        {337, 235, 3.5f, 18.0f, 1.2f}  // Level 3
    };
}

/**
 * @brief Attacks a vector of critters, dealing damage to all critters within range.
 * 
 * The tower damages all critters within its range.  The damage dealt is a percentage of the tower's power.
 * 
 * @param targets A vector of pointers to Critter objects that can be attacked.
 */
void AoETower::attack(std::vector<Critter*>& targets) {
    for(Critter* c : targets) {
        if(isInRange(0, 0, c->getX(), c->getY())) {
            c->takeDamage(levels[currentLevel].power * 0.6f); // 60% of the power we can change this later
        }
    }
}