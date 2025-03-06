#include "critter.h"
#include <iostream>
#include <iostream>
#include "map.h"
#include <cmath>
#include "Observable.h"
#include "Observer.h"

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
Critter::Critter(int id, int hitpoints, int reward, int strength, double speed, int level)
    : id(id), hitpoints(hitpoints), reward(reward), strength(strength), speed(speed), level(level), x(0.0f), y(0.0f) {}

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


void Critter::notifyObservers() {
    for(auto observer : observers) {
        observer->update(this);
    }
}

/**
 * @brief Sets the properties of the critter.
 * @param id The ID of the critter.
 * @param hitpoints The hitpoints of the critter.
 * @param reward The reward for killing the critter.
 * @param strength The strength of the critter.
 * @param speed The speed of the critter.
 * @param level The level of the critter.
 */
void Critter::setId(int id) {this->id = id;notifyObservers();}
void Critter::setHitpoints(int hitPoints) {this->hitpoints = hitPoints;notifyObservers();}
void Critter::setReward(int reward) {this->reward = reward;notifyObservers();}
void Critter::setStrength(int strength) {this->strength = strength;notifyObservers();}
void Critter::setSpeed(double speed) {this->speed = speed;notifyObservers();}
void Critter::setLevel(int level) {this->level = level;notifyObservers();}
/**
 * @brief Sets the position of the critter.
 * @param newX The new X position.
 * @param newY The new Y position.
 */
void Critter::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
    notifyObservers();
}

/**
 * @brief Reduces the hitpoints of the critter by the given damage.
 * @param damage The amount of damage to take.
 */
void Critter::takeDamage(int damage) {
    hitpoints -= damage;
    if (hitpoints < 0) hitpoints = 0;
    notifyObservers();
}

/**
 * @brief Checks if the critter is alive.
 * @return True if the critter is alive, false otherwise.
 */
bool Critter::isAlive() const {
    return hitpoints > 0;
}

/**
 * @brief Moves the critter on the game map.
 * @param map The game map.
 */
void Critter::move(gameMap& map) {
    int exitX = map.getExitX();
    int exitY = map.getExitY();

    if (exitX == -1 || exitY == -1) {
        cout << "Error: Exit not set!" << endl;
        return;
    }

    // Try moving along X axis first
    if (abs(exitX - x) > abs(exitY - y)) {
        if (x < exitX && map.canCritterMove(static_cast<int>(x + 1), static_cast<int>(y))) {
            setPosition(x + 1, y);
        } else if (x > exitX && map.canCritterMove(static_cast<int>(x - 1), static_cast<int>(y))) {
            setPosition(x - 1, y);
        }
        // If cannot move on X, try Y
        else if (y < exitY && map.canCritterMove(static_cast<int>(x), static_cast<int>(y + 1))) {
            setPosition(x, y + 1);
        } else if (y > exitY && map.canCritterMove(static_cast<int>(x), static_cast<int>(y - 1))) {
            setPosition(x, y - 1);
        }
    }
    // Otherwise, try moving along Y axis first
    else {
        if (y < exitY && map.canCritterMove(static_cast<int>(x), static_cast<int>(y + 1))) {
            setPosition(x, y + 1);
        } else if (y > exitY && map.canCritterMove(static_cast<int>(x), static_cast<int>(y - 1))) {
            setPosition(x, y - 1);
        }
        // If cannot move on Y, try X
        else if (x < exitX && map.canCritterMove(static_cast<int>(x + 1), static_cast<int>(y))) {
            setPosition(x + 1, y);
        } else if (x > exitX && map.canCritterMove(static_cast<int>(x - 1), static_cast<int>(y))) {
            setPosition(x - 1, y);
        }
    }

    cout << "Critter #" << id << " moving to (" << x << ", " << y << ")" << endl;

    notifyObservers();
}