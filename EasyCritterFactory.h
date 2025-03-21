#ifndef EASYCRITTERFACTORY_H
#define EASYCRITTERFACTORY_H

#include "CritterFactory.h"

class EasyCritterFactory : public CritterFactory {
public:
    Critter* createCritter(int id, int waveNumber) override;
};

#endif