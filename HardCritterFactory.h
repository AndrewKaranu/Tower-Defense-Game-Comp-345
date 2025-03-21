#ifndef HARDCRITTERFACTORY_H
#define HARDCRITTERFACTORY_H

#include "CritterFactory.h"

class HardCritterFactory : public CritterFactory {
public:
    Critter* createCritter(int id, int waveNumber) override;
};

#endif // HARDCRITTERFACTORY_H