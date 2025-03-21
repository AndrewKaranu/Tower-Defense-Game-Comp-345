#include "HardCritterFactory.h"
#include "critter.h"

Critter* HardCritterFactory::createCritter(int id, int waveNumber) {
    int hitpoints = 200 + waveNumber * 15;
    int reward = 30 + waveNumber * 5;
    int strength = 3 + waveNumber;
    double speed = 2.0 + waveNumber * 0.1;
    int level = waveNumber;

    return new Critter(id, hitpoints, reward, strength, speed, level);
}