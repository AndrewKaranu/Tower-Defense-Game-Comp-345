#ifndef CRITTER_H
#define CRITTER_H

class gameMap;

/**
 * @brief Represents a Critter in the game.
 */
class Critter {
private:
    int id;
    int hitpoints;
    int reward;
    int strength;
    double speed;
    int level;
    float x, y;

public:
    /**
     * @brief Default constructor for the Critter class.
     */
    Critter();
    /**
     * @brief Constructor for the Critter class.
     * @param id The ID of the critter.
     * @param hitpoints The hitpoints of the critter.
     * @param reward The reward for killing the critter.
     * @param strength The strength of the critter.
     * @param speed The speed of the critter.
     * @param level The level of the critter.
     */
    Critter(int id, int hitpoints, int reward, int strength, double speed, int level);

    /**
     * @brief Gets the properties of the critter.
     * @return The requested property of the critter.
     */
    int getId() const;
    int getHitpoints() const;
    int getReward() const;
    int getStrength() const;
    double getSpeed() const;
    int getLevel() const;

    /**
     * @brief Sets the properties of the critter.
     * @param id The ID of the critter.
     * @param hitpoints The hitpoints of the critter.
     * @param reward The reward for killing the critter.
     * @param strength The strength of the critter.
     * @param speed The speed of the critter.
     * @param level The level of the critter.
     */
    void setId(int id);
    void setHitpoints(int hitpoints);
    void setReward(int reward);
    void setStrength(int strength);
    void setSpeed(double speed);
    void setLevel(int level);

    /**
     * @brief Reduces the hitpoints of the critter by the given damage.
     * @param damage The amount of damage to take.
     */
    void takeDamage(int damage);

    /**
     * @brief Checks if the critter is alive.
     * @return True if the critter is alive, false otherwise.
     */
    bool isAlive() const;

    /**
     * @brief Moves the critter on the game map.
     * @param map The game map.
     */
    void move(gameMap& map);

    /**
     * @brief Gets the X position of the critter.
     * @return The X position of the critter.
     */
    float getX() const;
    /**
     * @brief Gets the Y position of the critter.
     * @return The Y position of the critter.
     */
    float getY() const;
    /**
     * @brief Sets the position of the critter.
     * @param newX The new X position.
     * @param newY The new Y position.
     */
    void setPosition(float newX, float newY);
};


#endif //CRITTER_H