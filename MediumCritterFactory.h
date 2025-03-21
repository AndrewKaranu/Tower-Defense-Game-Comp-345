#ifndef MEDIUMCRITTERFACTORY_H
#define MEDIUMCRITTERFACTORY_H

#include "CritterFactory.h"

class MediumCritterFactory : public CritterFactory {
public:
    Critter* createCritter(int id, int waveNumber) override;
};

#endif // MEDIUMCRITTERFACTORY_H