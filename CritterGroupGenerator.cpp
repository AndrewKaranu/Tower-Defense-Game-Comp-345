#include "CritterGroupGenerator.h"
#include <cstdlib>

/**
 * @brief Default constructor for the CritterGroupGenerator class.
 */
CritterGroupGenerator::CritterGroupGenerator() : waveNumber(1), nextCritterId(1) {}

/**
 * @brief Destructor for the CritterGroupGenerator class.
 */
CritterGroupGenerator::~CritterGroupGenerator() {}

/**
 * @brief Generates an array of critters for a given wave number.
 * @param waveNumber The wave number for which to generate critters.
 * @param numCritters The number of critters to generate.
 * @return A pointer to an array of Critter objects.
 */
Critter* CritterGroupGenerator::generateCritters(int waveNumber, int &numCritters) {
    return generateCritters(waveNumber, numCritters, -1, -1); // Call the other version with default values
}

/**
 * @brief Generates an array of critters for a given wave number with specified entry coordinates.
 * @param waveNumber The wave number for which to generate critters.
 * @param numCritters The number of critters to generate.
 * @param entryX The X coordinate of the entry point for the critters.
 * @param entryY The Y coordinate of the entry point for the critters.
 * @return A pointer to an array of Critter objects.
 */
Critter* CritterGroupGenerator::generateCritters(int waveNumber, int &numCritters, int entryX, int entryY) {
    this->waveNumber = waveNumber;

    numCritters = 5 + waveNumber * 2; // Generate multiple critters based on the wave.

    Critter* critters = new Critter[numCritters];
    for (int i = 0; i < numCritters; i++) {
        int hitpoints = 10 + waveNumber * 5;
        int reward = 2 + waveNumber;
        int strength = waveNumber + 1;
        int speed = 1 + waveNumber * 0.1;
        int level = waveNumber;

        critters[i] = Critter(nextCritterId++, hitpoints, reward, strength, speed, level);
        critters[i].setPosition(static_cast<float>(entryX), static_cast<float>(entryY)); // Set initial position
    }

    return critters;
}

/**
 * @brief Resets the generator to its initial state.
 */
void CritterGroupGenerator::reset() {
    waveNumber = 1;
    nextCritterId = 1;
}