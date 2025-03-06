#pragma once
#include "critter.h"
#include "Observable.h"
#include <vector>

class CritterGroup : public Observable {
private:
    std::vector<Critter*> critters;

public:
    CritterGroup();
    ~CritterGroup();

    void addCritter(Critter* critter);
    void removeCritter(Critter* critter);
    void removeCritterById(int id);
    Critter* getCritterById(int id);
    const std::vector<Critter*>& getAllCritters() const;
    int getCritterCount() const;

    void notifyObservers() override;
};