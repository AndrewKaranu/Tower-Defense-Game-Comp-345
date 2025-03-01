// CritterGroup.cpp
#include "CritterGroup.h"
#include <algorithm>

CritterGroup::CritterGroup() {}

CritterGroup::~CritterGroup() {
    // Delete all critters
    for (auto critter : critters) {
        delete critter;
    }
    critters.clear();
}

void CritterGroup::addCritter(Critter* critter) {
    critters.push_back(critter);
    notifyObservers();
}

void CritterGroup::removeCritter(Critter* critter) {
    auto it = std::find(critters.begin(), critters.end(), critter);
    if (it != critters.end()) {
        critters.erase(it);
        notifyObservers();
    }
}

void CritterGroup::removeCritterById(int id) {
    for (auto it = critters.begin(); it != critters.end(); ++it) {
        if ((*it)->getId() == id) {
            critters.erase(it);
            notifyObservers();
            break;
        }
    }
}

Critter* CritterGroup::getCritterById(int id) {
    for (auto critter : critters) {
        if (critter->getId() == id) {
            return critter;
        }
    }
    return nullptr;
}

const std::vector<Critter*>& CritterGroup::getAllCritters() const {
    return critters;
}

int CritterGroup::getCritterCount() const {
    return critters.size();
}

void CritterGroup::notifyObservers() {
    for (auto observer : observers) {
        observer->update(this);
    }
}