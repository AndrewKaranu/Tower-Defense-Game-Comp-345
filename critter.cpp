#include "critter.h"
#include <iostream>
#include <iostream>
#include "map.h"
#include <cmath>
using namespace std;

/**
 * @brief Default constructor for the Critter class.
 */
Critter::Critter() : id(0), hitpoints(0), reward(0), strength(0), speed(0.0), level(0), x(0.0f), y(0.0f) {}

/**
 * @brief Constructor for the Critter class.
 * @param id The ID of the critter.
 * @param hitpoints The hitpoints of the critter.
 * @param reward The reward for killing the critter.
 * @param strength The strength of the critter.
 * @param speed The speed of the critter.
 * @param level The level of the critter.
 */
Critter::Critter(int id, int hp, int reward, int strength, double speed, int level)
    : id(id), hitpoints(hp), reward(reward), strength(strength),
      speed(speed), originalSpeed(speed), level(level), 
      x(0.0f), y(0.0f), slowDuration(0.0)
{
}

/**
 * @brief Gets the properties of the critter.
 * @return The requested property of the critter.
 */
int Critter::getId() const {return id;}
int Critter::getHitpoints() const {return hitpoints;}
int Critter::getReward() const {return reward;}
int Critter::getStrength() const {return strength;}
double Critter::getSpeed() const {return speed;}
int Critter::getLevel() const {return level;}
float Critter::getX() const { return x; }
float Critter::getY() const { return y; }

/**
 * @brief Sets the properties of the critter.
 * @param id The ID of the critter.
 * @param hitpoints The hitpoints of the critter.
 * @param reward The reward for killing the critter.
 * @param strength The strength of the critter.
 * @param speed The speed of the critter.
 * @param level The level of the critter.
 */
void Critter::setId(int id) {this->id = id;}
void Critter::setHitpoints(int hitPoints) {this->hitpoints = hitPoints;}
void Critter::setReward(int reward) {this->reward = reward;}
void Critter::setStrength(int strength) {this->strength = strength;}
void Critter::setLevel(int level) {this->level = level;}
/**
 * @brief Sets the position of the critter.
 * @param newX The new X position.
 * @param newY The new Y position.
 */
void Critter::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

/**
 * @brief Reduces the hitpoints of the critter by the given damage.
 * @param damage The amount of damage to take.
 */
void Critter::takeDamage(int damage) {
    if (damage <= 0) return;  // Safety check

    // Apply damage
    hitpoints = std::max(0, hitpoints - damage);
    
    // Debug output to track damage
    std::cout << "Critter #" << id << " took " << damage << " damage, hitpoints now: " << hitpoints << std::endl;
}

/**
 * @brief Checks if the critter is alive.
 * @return True if the critter is alive, false otherwise.
 */
bool Critter::isAlive() const {
    return hitpoints > 0;
}

void Critter::updateSlowEffect(double deltaTime) {
    if (slowDuration > 0) {
        // Reduce slow duration
        slowDuration -= deltaTime;
        
        // Reset speed when slow effect expires
        if (slowDuration <= 0) {
            speed = originalSpeed;
            slowDuration = 0;
        }
    }
}

void Critter::move(gameMap& map) {
    int exitX = map.getExitX();
    int exitY = map.getExitY();

    // Debug output to help track movement
    std::cout << "Critter #" << id << " at (" << x << ", " << y 
              << ") moving towards exit at (" << exitX << ", " << exitY << ")" << std::endl;

    if (exitX == -1 || exitY == -1) {
        std::cout << "Error: Exit not set!" << std::endl;
        return;
    }

    bool moved = false;

    // Try moving along X axis first
    if (abs(exitX - x) > abs(exitY - y)) {
        if (x < exitX && map.canCritterMove(static_cast<int>(x + 1), static_cast<int>(y))) {
            setPosition(x + 1, y);
            moved = true;
        } else if (x > exitX && map.canCritterMove(static_cast<int>(x - 1), static_cast<int>(y))) {
            setPosition(x - 1, y);
            moved = true;
        }
    }
    // Try moving along Y axis if not moved
    if (!moved) {
        if (y < exitY && map.canCritterMove(static_cast<int>(x), static_cast<int>(y + 1))) {
            setPosition(x, y + 1);
            moved = true;
        } else if (y > exitY && map.canCritterMove(static_cast<int>(x), static_cast<int>(y - 1))) {
            setPosition(x, y - 1);
            moved = true;
        }
    }
    // If still not moved, try the other axis
    if (!moved) {
        if (x < exitX && map.canCritterMove(static_cast<int>(x + 1), static_cast<int>(y))) {
            setPosition(x + 1, y);
        } else if (x > exitX && map.canCritterMove(static_cast<int>(x - 1), static_cast<int>(y))) {
            setPosition(x - 1, y);
        } else if (y < exitY && map.canCritterMove(static_cast<int>(x), static_cast<int>(y + 1))) {
            setPosition(x, y + 1);
        } else if (y > exitY && map.canCritterMove(static_cast<int>(x), static_cast<int>(y - 1))) {
            setPosition(x, y - 1);
        }
    }

    std::cout << "Critter #" << id << " moved to (" << x << ", " << y << ")" << std::endl;
}
