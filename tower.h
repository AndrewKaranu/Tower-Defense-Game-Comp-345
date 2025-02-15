#pragma once
#include <vector>
#include <iostream>

/**
 * @brief Represents the statistics for a specific level of a tower.
 */
struct LevelStats {
    float buyCost;      ///< The cost to purchase this level.
    float refundValue;  ///< The value refunded when selling this level.
    float range;        ///< The attack range of this level.
    float power;        ///< The attack power of this level.
    float fireRate;     ///< The rate at which this level can fire.
};

class Critter;

/**
 * @brief The base class for all towers.
 * 
 * Defines the core functionality and attributes of a tower, including attacking, upgrading, and selling.
 */
class Tower {
protected:
    size_t currentLevel;                  ///< The current level of the tower.
    std::vector<LevelStats> levels;       ///< A vector containing the statistics for each level of the tower.
    
public:
    /**
     * @brief Default constructor for the Tower class.
     */
    Tower();
    /**
     * @brief Virtual destructor for the Tower class.
     */
    virtual ~Tower() = default;

    // Core functionality
    /**
     * @brief Attacks a vector of critters.
     * 
     * @param targets A vector of pointers to Critter objects that can be attacked.
     */
    virtual void attack(std::vector<Critter*>& targets) = 0;
    /**
     * @brief Upgrades the tower to the next level.
     * 
     * @return True if the upgrade was successful, false otherwise.
     */
    bool upgrade();
    /**
     * @brief Sells the tower and returns the refund value.
     * 
     * @return The refund value of the tower.
     */
    float sell() const;
    
    // Getters
    /**
     * @brief Gets a property of the tower.
     * 
     * @return The requested property of the tower.
     */
    float getRange() const;
    float getPower() const;
    size_t getLevel() const;
    float getFireRate() const;

    // Helper
    /**
     * @brief Checks if a critter is within the tower's attack range.
     * 
     * @param x The x-coordinate of the tower.
     * @param y The y-coordinate of the tower.
     * @param critterX The x-coordinate of the critter.
     * @param critterY The y-coordinate of the critter.
     * @return True if the critter is within range, false otherwise.
     */
    bool isInRange(float x, float y, float critterX, float critterY) const;
};