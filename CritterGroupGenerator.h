#ifndef CRITTERGROUPGENERATOR_H
#define CRITTERGROUPGENERATOR_H

#include "critter.h"

/**
 * @brief Class responsible for generating groups of critters for each wave.
 */
class CritterGroupGenerator {
private:
    int waveNumber;
    int nextCritterId;
public:
    /**
     * @brief Default constructor for the CritterGroupGenerator class.
     */
    CritterGroupGenerator();

    /**
     * @brief Destructor for the CritterGroupGenerator class.
     */
    ~CritterGroupGenerator();
    /**
     * @brief Generates an array of critters for a given wave number.
     * @param waveNumber The wave number for which to generate critters.
     * @param numCritters The number of critters to generate.
     * @return A pointer to an array of Critter objects.
     */
    Critter* generateCritters(int waveNumber, int& numCritters);
    /**
     * @brief Generates an array of critters for a given wave number with specified entry coordinates.
     * @param waveNumber The wave number for which to generate critters.
     * @param numCritters The number of critters to generate.
     * @param entryX The X coordinate of the entry point for the critters.
     * @param entryY The Y coordinate of the entry point for the critters.
     * @return A pointer to an array of Critter objects.
     */
    Critter* generateCritters(int waveNumber, int& numCritters, int entryX, int entryY);

    /**
     * @brief Resets the generator to its initial state.
     */
    void reset();
};



#endif //CRITTERGROUPGENERATOR_H