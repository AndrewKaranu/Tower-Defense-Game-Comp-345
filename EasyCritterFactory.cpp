#include "EasyCritterFactory.h"
#include "critter.h"

Critter* EasyCritterFactory::createCritter(int id, int waveNumber) {
    int hitpoints = 50 + waveNumber * 2;
    int reward = 10 + waveNumber * 2;
    int strength = 1 + waveNumber;
    double speed = 1.0 + waveNumber * 0.1;
    int level = waveNumber;

    return new Critter(id, hitpoints, reward, strength, speed, level);
}