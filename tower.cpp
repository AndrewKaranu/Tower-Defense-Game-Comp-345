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
 * @brief Gets the attack range of the tower.
 *
 * @return The attack range of the tower.
 */
float Tower::getRange() const { return levels[currentLevel].range; }

/**
 * @brief Gets the attack power of the tower.
 *
 * @return The attack power of the tower.
 */
float Tower::getPower() const { return levels[currentLevel].power; }

/**
 * @brief Gets the current level of the tower.
 *
 * @return The current level of the tower.
 */
size_t Tower::getLevel() const { return currentLevel + 1; }

/**
 * @brief Gets the fire rate of the tower.
 *
 * @return The fire rate of the tower.
 */
float Tower::getFireRate() const { return levels[currentLevel].fireRate; }

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

double Tower::getDistanceSquared(float x1, float y1, float x2, float y2) const {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return dx * dx + dy * dy;
}
