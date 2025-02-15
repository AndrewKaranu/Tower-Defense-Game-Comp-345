#include "CritterGroupGenerator.h"
#include <cstdlib>

/**
 * @brief Constructor for CritterGroupGenerator.
 * Initializes the wave number and next critter ID.
 */
CritterGroupGenerator::CritterGroupGenerator() : waveNumber(1), nextCritterId(1) {}

/**
 * @brief Destructor for CritterGroupGenerator.
 * Curently does not perform any cleanup as no dynamic resources are owned.
 * this is basically for cleaning up dynamically allocated memory
 */
CritterGroupGenerator::~CritterGroupGenerator() {
}

/**
 * @brief Generates a group of critters for the given wave number.
 * Based on the wave number, the number of critters, their hitpoints, reward, strength, speed, and level are calculated.
 *
 * @param waveNumber The current wave number, which affects the characteristics of the critters.
 * @param numCritters The reference to an integer that will hold the number of critters generated.
 * @return A pointer to an array of Critter objects representing the generated critters.
 */
Critter *CritterGroupGenerator::generateCritters(int waveNumber, int &numCritters) {
    this->waveNumber = waveNumber;

    // Calculate the number of critters for this wave
    numCritters = 5 + waveNumber * 2;

    // Allocate memory for critters
    Critter* critters = new Critter[numCritters];
    for (int i = 0; i < numCritters; i++) {
        // Set the attributes for each critter based on the wave number
        int hitpoints = 10 + waveNumber * 5;
        int reward = 2 + waveNumber;
        int strength = waveNumber + 1;
        int speed = 1 + waveNumber * 0.1;
        int level = waveNumber;

        // Create the critter with the calculated attributes
        critters[i] = Critter(nextCritterId++, hitpoints, reward, strength, speed, level);
    }

    return critters;
}

/**
 * @brief Resets the generator's state.
 *
 * Resets the wave number and next critter ID back to their initial values.
 */
void CritterGroupGenerator::reset() {
    waveNumber = 1;
    nextCritterId = 1;
}
