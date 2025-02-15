//
// Created by arash shafiee on 2025-02-11.
//

#include "CritterGroupGenerator.h"
#include <cstdlib>

CritterGroupGenerator::CritterGroupGenerator() : waveNumber(1), nextCritterId(1) {}

// for cleaning up dynamically allocated memory
CritterGroupGenerator::~CritterGroupGenerator() {
}

Critter *CritterGroupGenerator::generateCritters(int waveNumber, int &numCritters) {
    this->waveNumber = waveNumber;

    numCritters = 5 + waveNumber * 2;

    Critter* critters = new Critter[numCritters];
    for (int i = 0; i < numCritters; i++) {
        int hitpoints = 10 + waveNumber * 5;
        int reward = 2 + waveNumber;
        int strength = waveNumber + 1;
        int speed = 1 + waveNumber * 0.1;
        int level = waveNumber;

        critters[i] = Critter(nextCritterId++, hitpoints, reward, strength,speed, level);
    }

    return critters;

}

void CritterGroupGenerator::reset() {
    waveNumber = 1;
    nextCritterId = 1;
}