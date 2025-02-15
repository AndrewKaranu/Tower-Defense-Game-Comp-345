#include <iostream>
#include "CritterGroupGenerator.h"

int main() {
    CritterGroupGenerator generator;

    // Generate critters for wave 1
    int numCrittersWave1;
    Critter* wave1 = generator.generateCritters(1, numCrittersWave1);
    std::cout << "Wave 1 Critters:" << std::endl;
    for (int i = 0; i < numCrittersWave1; i++) {
        std::cout << "Critter #" << wave1[i].getId() << " (HP: " << wave1[i].getHitpoints()
                  << ", Reward: " << wave1[i].getReward() << ", Level: " << wave1[i].getLevel() << ")" << std::endl;
        wave1[i].move();
    }

    // Clean up dynamically allocated memory
    delete[] wave1;

    // Generate critters for wave 2
    int numCrittersWave2;
    Critter* wave2 = generator.generateCritters(2, numCrittersWave2);
    std::cout << "\nWave 2 Critters:" << std::endl;
    for (int i = 0; i < numCrittersWave2; i++) {
        std::cout << "Critter #" << wave2[i].getId() << " (HP: " << wave2[i].getHitpoints()
                  << ", Reward: " << wave2[i].getReward() << ", Level: " << wave2[i].getLevel() << ")" << std::endl;
        wave2[i].move();
    }

    // Clean up dynamically allocated memory
    delete[] wave2;

    return 0;
}
