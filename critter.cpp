#include "critter.h"
#include <iostream>
using namespace std;

/**
 * @brief Default constructor for Critter.
 * Initializes the critter with default values (id = 0, health = 0, etc.).
 */
Critter::Critter() : id(0), hitpoints(0), reward(0), strength(0), speed(0.0), level(0), x(0.0f), y(0.0f) {}

/**
 * @brief Parameterized constructor to initialize the critter with specific values.
 *
 * @param id The unique ID for the critter.
 * @param hitpoints The initial hitpoints (health) of the critter.
 * @param reward The reward for defeating the critter.
 * @param strength The strength of the critter.
 * @param speed The speed of the critter.
 * @param level The level of the critter.
 */
Critter::Critter(int id, int hitpoints, int reward, int strength, double speed, int level)
    : id(id), hitpoints(hitpoints), reward(reward), strength(strength), speed(speed), level(level), x(0.0f), y(0.0f) {}

/**
 * @brief Gets the critter's unique ID.
 *
 * @return The critter's ID.
 */
int Critter::getId() const { return id; }

/**
 * @brief Gets the critter's current hitpoints.
 *
 * @return The current hitpoints of the critter.
 */
int Critter::getHitpoints() const { return hitpoints; }

/**
 * @brief Gets the reward for defeating the critter.
 *
 * @return The reward for defeating the critter.
 */
int Critter::getReward() const { return reward; }

/**
 * @brief Gets the critter's strength.
 *
 * @return The critter's strength.
 */
int Critter::getStrength() const { return strength; }

/**
 * @brief Gets the critter's speed.
 *
 * @return The speed of the critter.
 */
double Critter::getSpeed() const { return speed; }

/**
 * @brief Gets the critter's level.
 *
 * @return The critter's level.
 */
int Critter::getLevel() const { return level; }

/**
 * @brief Gets the x-coordinate of the critter's position.
 *
 * @return The x-coordinate of the critter.
 */
float Critter::getX() const { return x; }

/**
 * @brief Gets the y-coordinate of the critter's position.
 *
 * @return The y-coordinate of the critter.
 */
float Critter::getY() const { return y; }

/**
 * @brief Sets the critter's unique ID.
 *
 * @param id The unique ID to assign to the critter.
 */
void Critter::setId(int id) { this->id = id; }

/**
 * @brief Sets the critter's hitpoints.
 *
 * @param hitPoints The value to set the critter's hitpoints.
 */
void Critter::setHitpoints(int hitPoints) { this->hitpoints = hitPoints; }

/**
 * @brief Sets the reward for defeating the critter.
 *
 * @param reward The value to set the critter's reward.
 */
void Critter::setReward(int reward) { this->reward = reward; }

/**
 * @brief Sets the critter's strength.
 *
 * @param strength The value to set the critter's strength.
 */
void Critter::setStrength(int strength) { this->strength = strength; }

/**
 * @brief Sets the critter's speed.
 *
 * @param speed The value to set the critter's speed.
 */
void Critter::setSpeed(double speed) { this->speed = speed; }

/**
 * @brief Sets the critter's level.
 *
 * @param level The value to set the critter's level.
 */
void Critter::setLevel(int level) { this->level = level; }

/**
 * @brief Sets the critter's position to new x and y coordinates.
 *
 * @param newX The new x-coordinate to set.
 * @param newY The new y-coordinate to set.
 */
void Critter::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

/**
 * @brief Reduces the critter's hitpoints by the specified damage value.
 *
 * This method is used when the critter takes damage. If hitpoints go below 0, they are set to 0.
 *
 * @param damage The amount of damage to inflict on the critter.
 */
void Critter::takeDamage(int damage) {
    hitpoints -= damage;
    if (hitpoints < 0) hitpoints = 0;
}

/**
 * @brief Checks if the critter is still alive.
 *
 * @return True if the critter's hitpoints are greater than 0, indicating it is alive.
 *         False if the critter has no remaining hitpoints.
 */
bool Critter::isAlive() const {
    return hitpoints > 0;
}

/**
 * @brief Moves the critter.
 *
 * The critter moves at its specified speed, and a message is displayed indicating its movement.
 */
void Critter::move() {
    cout << "Critter #" << id << " is moving at the speed of " << speed << " towards the exit!" << endl;
}
