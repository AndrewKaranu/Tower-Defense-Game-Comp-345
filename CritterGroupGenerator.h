//
// Created by arash shafiee on 2025-02-11.
//

#ifndef CRITTERGROUPGENERATOR_H
#define CRITTERGROUPGENERATOR_H

#include "Critter.h"

class CritterGroupGenerator {
private:
    int waveNumber;
    int nextCritterId;
    public:
    CritterGroupGenerator();

    ~CritterGroupGenerator();

    Critter* generateCritters(int waveNumber, int& numCritters);

    void reset();
};



#endif //CRITTERGROUPGENERATOR_H
