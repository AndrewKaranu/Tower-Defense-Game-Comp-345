#include "MediumCritterFactory.h"
#include "critter.h"

Critter* MediumCritterFactory::createCritter(int id, int waveNumber) {
    int hitpoints = 100 + waveNumber * 10;
    int reward = 20 + waveNumber * 3;
    int strength = 2 + waveNumber;
    double speed = 1.5 + waveNumber * 0.1;
    int level = waveNumber;

    return new Critter(id, hitpoints, reward, strength, speed, level);
}