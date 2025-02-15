#ifndef CRITTERGROUPGENERATOR_H
#define CRITTERGROUPGENERATOR_H

#include "critter.h"

/**
 * @class CritterGroupGenerator
 * @brief A class that generates groups of critters based on the current wave number.
 *
 * This class is responsible for creating a specified number of critters with
 * attributes based on the wave number. It also handles resetting its internal state.
 */
class CritterGroupGenerator {
private:
    /**
     * @brief The current wave number.
     * It determines the characteristics of the generated critters, like hitpoints, reward, etc.
     */
    int waveNumber;

    /**
     * @brief The ID for the next critter to be created.
     * It is incremented each time a new critter is generated.
     */
    int nextCritterId;

public:
    /**
     * @brief Constructor for CritterGroupGenerator.
     * Initializes the wave number and next critter ID.
     */
    CritterGroupGenerator();

    /**
     * @brief Destructor for CritterGroupGenerator.
     * Currently does not perform any cleanup as no dynamic resources are owned.
     */
    ~CritterGroupGenerator();

    /**
     * @brief Generates a group of critters for the given wave number.
     *
     * Based on the wave number, the number of critters, their hitpoints, reward, strength, speed, and level are calculated.
     *
     * @param waveNumber The current wave number, which affects the characteristics of the critters.
     * @param numCritters The reference to an integer that will hold the number of critters generated.
     * @return A pointer to an array of Critter objects representing the generated critters.
     */
    Critter* generateCritters(int waveNumber, int& numCritters);

    /**
     * @brief Resets the generator's state.
     *
     * Resets the wave number and next critter ID back to their initial values.
     */
    void reset();
};

#endif //CRITTERGROUPGENERATOR_H
