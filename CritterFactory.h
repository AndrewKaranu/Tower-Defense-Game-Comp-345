#ifndef PROJECT_CRITTERFACTORY_H
#define PROJECT_CRITTERFACTORY_H

#include "critter.h"

class CritterFactory {
public:
    virtual ~CritterFactory() = default;
    virtual Critter* createCritter(int id, int waveNumber) = 0;
};
#endif //PROJECT_CRITTERFACTORY_H
