#include "CritterGroupGenerator.h"
#include "EasyCritterFactory.h"
#include "MediumCritterFactory.h"
#include "HardCritterFactory.h"

/**
 * @brief Default constructor for the CritterGroupGenerator class.
 */
CritterGroupGenerator::CritterGroupGenerator() : waveNumber(1), nextCritterId(1) {
    factories.push_back(new EasyCritterFactory());
    factories.push_back(new MediumCritterFactory());
    factories.push_back(new HardCritterFactory());
}

/**
 * @brief Destructor for the CritterGroupGenerator class.
 */
CritterGroupGenerator::~CritterGroupGenerator() {
    // Cleaning up factories
    for (auto factory : factories) {
        delete factory;
    }
}

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

    // factory to use based on wave number
    CritterFactory* factory = nullptr;
    if (waveNumber <= 3) {
        factory = factories[0]; // EasyCritterFactory
    } else if (waveNumber <= 6) {
        factory = factories[1]; // MediumCritterFactory
    } else {
        factory = factories[2]; // HardCritterFactory
    }


    numCritters = 5 + waveNumber * 2; // Generate multiple critters based on the wave.

    Critter* critters = new Critter[numCritters];

    for (int i = 0; i < numCritters; i++) {
        // Use the factory to create a critter
        critters[i] = *factory->createCritter(nextCritterId++, waveNumber);
        critters[i].setPosition(static_cast<float>(entryX), static_cast<float>(entryY));
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
