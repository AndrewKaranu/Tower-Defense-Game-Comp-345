#pragma once
#include "tower.h"
#include "critter.h"
#include <vector>

/**
 * @brief Represents a tower that slows down critters.
 * 
 * This class inherits from the Tower class and overrides the attack method to apply a slowing effect to the targeted critters.
 */
class SlowTower : public Tower {
public:
    /**
     * @brief Constructor for the SlowTower class.
     */
    SlowTower();
    /**
     * @brief Attacks a vector of critters, applying a slowing effect.
     * 
     * @param targets A vector of pointers to Critter objects that can be attacked.
     */
    void attack(std::vector<Critter*>& targets) override;
    
private:
    std::vector<float> slowPercentages;  ///< The percentage by which the critter's movement speed is reduced at each level.
    /**
     * @brief Applies the slowing effect to a critter.
     * 
     * @param critter A pointer to the Critter object to which the slowing effect is applied.
     */
    void applySlow(Critter* critter);
};