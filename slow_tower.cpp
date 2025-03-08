#include "slow_tower.h"
#include "critter.h"
#include <vector>
#include <iostream>

/**
 * @brief Constructor for the SlowTower class.
 * 
 * Initializes the levels vector with the statistics for each level.
 * Slow tower has 0 damage but applies a speed debuff.
 */
SlowTower::SlowTower() {
    // Set power values to 0 for slow tower - it doesn't deal damage
    levels = {
        {150, 0, 3.5f, 7.0f, 1.0f},   // Level 1 - no damage
        {225, 0, 4.0f, 10.0f, 1.2f},  // Level 2 - no damage
        {337, 0, 4.5f, 15.0f, 1.5f}   // Level 3 - no damage
    };
    
    // Initialize slow percentages for each level
    slowPercentages = {0.3f, 0.5f, 0.7f};  // Increased slow effect to compensate for no damage
}

void SlowTower::attack(std::vector<Critter*>& targets) {
    // Slow tower doesn't deal damage, only slows targets
    for (Critter* target : targets) {
        if (!target || !target->isAlive()) continue;
        
        // Apply slowing effect only
        applySlow(target);
        
        // Debug output
        std::cout << "SlowTower slowed critter #" << target->getId() 
                  << " by " << (slowPercentages[currentLevel] * 100) << "%"
                  << " (no damage)" << std::endl;
    }
}

void SlowTower::applySlow(Critter* critter) {
    if (!critter) return;
    
    // Get original speed before any slow effects
    double originalSpeed = critter->getOriginalSpeed();
    
    // Calculate new speed with slow effect based on tower level
    double slowPercentage = slowPercentages[currentLevel];
    double newSpeed = originalSpeed * (1.0 - slowPercentage);
    
    // Apply the slow effect
    critter->setSpeed(newSpeed);
    
    // Set a timer to restore speed after a duration - increase duration with tower level
    double slowDuration = 3.0 + currentLevel * 1.0; // 3, 4, or 5 seconds based on level
    critter->setSlowDuration(slowDuration);
}