#pragma once
#include "tower.h"

/**
 * @brief Represents an area-of-effect tower.
 *
 * This class inherits from the Tower class and implements an attack strategy that damages all critters within its range.
 */
class AoETower : public Tower {
public:
    /**
     * @brief Constructor for the AoETower class.
     */
    AoETower();
    /**
     * @brief Attacks a vector of critters, dealing damage to all critters within range.
     *
     * @param targets A vector of pointers to Critter objects that can be attacked.
     */
    void attack(std::vector<Critter*>& targets) override;
};
