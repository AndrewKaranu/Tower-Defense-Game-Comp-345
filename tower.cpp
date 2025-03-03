#include "tower.h"
#include "critter.h"

/**
 * @brief Constructor for the Tower class.
 * 
 * Initializes the current level to 0.
 */
Tower::Tower() : currentLevel(0) {}

/**
 * @brief Upgrades the tower to the next level.
 * 
 * If the tower is not already at the maximum level, it increments the current level.
 * 
 * @return True if the upgrade was successful, false otherwise.
 */
bool Tower::upgrade() {
    if(currentLevel + 1 < levels.size()) {
        currentLevel++;
        notifyObservers(); // Notify observers when tower is upgraded
        return true;
    }
    return false;
}

/**
 * @brief Sells the tower and returns the refund value.
 * 
 * @return The refund value of the tower.
 */
float Tower::sell() const {
    return levels[currentLevel].refundValue;
}

/**
 * @brief Sets the position of the tower.
 * 
 * @param x The x-coordinate of the tower.
 * @param y The y-coordinate of the tower.
 */
void Tower::setPosition(int x, int y) {
    posX = x;
    posY = y;
    notifyObservers(); // Notify observers when position changes
}

/**
 * @brief Gets the x-coordinate of the tower.
 * 
 * @return The x-coordinate of the tower.
 */
int Tower::getPositionX() const {
    return posX;
}

/**
 * @brief Gets the y-coordinate of the tower.
 * 
 * @return The y-coordinate of the tower.
 */
int Tower::getPositionY() const {
    return posY;
}

/**
 * @brief Gets the attack range of the tower.
 * 
 * @return The attack range of the tower.
 */
float Tower::getRange() const { 
    return levels[currentLevel].range; 
}

/**
 * @brief Gets the attack power of the tower.
 * 
 * @return The attack power of the tower.
 */
float Tower::getPower() const { 
    return levels[currentLevel].power; 
}

/**
 * @brief Gets the current level of the tower.
 * 
 * @return The current level of the tower.
 */
size_t Tower::getLevel() const { 
    return currentLevel + 1; 
}

/**
 * @brief Gets the fire rate of the tower.
 * 
 * @return The fire rate of the tower.
 */
float Tower::getFireRate() const { 
    return levels[currentLevel].fireRate; 
}

/**
 * @brief Gets the buy cost of the tower.
 * 
 * @return The buy cost of the tower.
 */
float Tower::getBuyCost() const {
    return levels[currentLevel].buyCost;
}

/**
 * @brief Gets the refund value of the tower.
 * 
 * @return The refund value of the tower.
 */
float Tower::getRefundValue() const {
    return levels[currentLevel].refundValue;
}

/**
 * @brief Checks if a critter is within the tower's attack range.
 * 
 * @param x The x-coordinate of the tower.
 * @param y The y-coordinate of the tower.
 * @param critterX The x-coordinate of the critter.
 * @param critterY The y-coordinate of the critter.
 * @return True if the critter is within range, false otherwise.
 */
bool Tower::isInRange(float x, float y, float critterX, float critterY) const {
    float dx = x - critterX;
    float dy = y - critterY;
    return (dx*dx + dy*dy) <= (levels[currentLevel].range * levels[currentLevel].range);
}