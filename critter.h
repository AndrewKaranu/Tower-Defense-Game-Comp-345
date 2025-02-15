#ifndef CRITTER_H
#define CRITTER_H

/**
 * @class Critter
 * @brief A class that represents a critter in the game.
 *
 * A critter has various attributes like hitpoints, strength, speed, and level.
 * It can take damage, move, and has a position (x, y) on the screen.
 */
class Critter {
private:
    /** @brief Unique identifier for the critter. */
    int id;

    /** @brief The hitpoints of the critter, representing its health. */
    int hitpoints;

    /** @brief The reward given when the critter is defeated. */
    int reward;

    /** @brief The strength of the critter, used for determining damage. */
    int strength;

    /** @brief The speed of the critter, used to determine its movement speed. */
    double speed;

    /** @brief The level of the critter, affecting its overall power. */
    int level;

    /** @brief The x and y coordinates representing the critter's position on the screen. */
    float x, y;

public:
    /**
     * @brief Default constructor for Critter.
     * Initializes the critter with default values (id = 0, etc.).
     */
    Critter();

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
    Critter(int id, int hitpoints, int reward, int strength, double speed, int level);

    /**
     * @brief Gets the critter's unique ID.
     *
     * @return The critter's ID.
     */
    int getId() const;

    /**
     * @brief Gets the critter's current hitpoints.
     *
     * @return The current hitpoints.
     */
    int getHitpoints() const;

    /**
     * @brief Gets the reward for defeating the critter.
     *
     * @return The reward.
     */
    int getReward() const;

    /**
     * @brief Gets the critter's strength.
     *
     * @return The critter's strength.
     */
    int getStrength() const;

    /**
     * @brief Gets the critter's speed.
     *
     * @return The speed of the critter.
     */
    double getSpeed() const;

    /**
     * @brief Gets the critter's level.
     *
     * @return The critter's level.
     */
    int getLevel() const;

    /**
     * @brief Sets the critter's unique ID.
     *
     * @param id The unique ID to assign to the critter.
     */
    void setId(int id);

    /**
     * @brief Sets the critter's hitpoints.
     *
     * @param hitpoints The value to set the critter's hitpoints.
     */
    void setHitpoints(int hitpoints);

    /**
     * @brief Sets the reward for defeating the critter.
     *
     * @param reward The value to set the critter's reward.
     */
    void setReward(int reward);

    /**
     * @brief Sets the critter's strength.
     *
     * @param strength The value to set the critter's strength.
     */
    void setStrength(int strength);

    /**
     * @brief Sets the critter's speed.
     *
     * @param speed The value to set the critter's speed.
     */
    void setSpeed(double speed);

    /**
     * @brief Sets the critter's level.
     *
     * @param level The value to set the critter's level.
     */
    void setLevel(int level);

    /**
     * @brief Reduces the critter's hitpoints by the specified damage value.
     *
     * This method is used when the critter takes damage.
     *
     * @param damage The amount of damage to inflict on the critter.
     */
    void takeDamage(int damage);

    /**
     * @brief Checks if the critter is still alive.
     *
     * @return True if the critter's hitpoints are greater than 0, indicating it is alive.
     *         False if the critter has no remaining hitpoints.
     */
    bool isAlive() const;

    /**
     * @brief Moves the critter.
     *
     * The movement logic can be implemented here, such as moving the critter along its path or towards a target.
     */
    void move();

    /**
     * @brief Gets the x-coordinate of the critter's position.
     *
     * @return The x-coordinate of the critter.
     */
    float getX() const;

    /**
     * @brief Gets the y-coordinate of the critter's position.
     *
     * @return The y-coordinate of the critter.
     */
    float getY() const;

    /**
     * @brief Sets the critter's position to new x and y coordinates.
     *
     * @param newX The new x-coordinate to set.
     * @param newY The new y-coordinate to set.
     */
    void setPosition(float newX, float newY);
};

#endif //CRITTER_H
