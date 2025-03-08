#pragma once
#include "tower.h"

/**
 * @brief Represents a basic tower.
 *
 * This class inherits from the Tower class and implements a simple attack strategy.
 */
class BasicTower : public Tower {
public:
    /**
     * @brief Constructor for the BasicTower class.
     */
    BasicTower();
    /**
     * @brief Attacks a vector of critters.
     *
     * @param targets A vector of pointers to Critter objects that can be attacked.
     */
    void attack(std::vector<Critter*>& targets) override;
};
