#include "CritterGroupObserver.h"
#include <iostream>

CritterGroupObserver::CritterGroupObserver(const std::string& name) : name(name) {
}

void CritterGroupObserver::update(Observable* observable) {
    CritterGroup* group = static_cast<CritterGroup*>(observable);

    std::cout << "\n===== " << name << ": Critter Group Update =====" << std::endl;
    std::cout << "Total critters: " << group->getCritterCount() << std::endl;

    const auto& critters = group->getAllCritters();
    for (size_t i = 0; i < critters.size(); ++i) {
        std::cout << "Critter #" << i + 1 << " (ID: " << critters[i]->getId() << "):" << std::endl;
        std::cout << "  Position: (" << critters[i]->getX() << ", " << critters[i]->getY() << ")" << std::endl;
        std::cout << "  Hitpoints: " << critters[i]->getHitpoints() << std::endl;
    }
    std::cout << "==================================\n" << std::endl;
}