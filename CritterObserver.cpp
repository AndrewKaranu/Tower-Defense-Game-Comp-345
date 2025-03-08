#include "CritterObserver.h"
#include <iostream>

CritterObserver::CritterObserver(Critter* c) : subject(c) {
    subject->attach(this);
}

CritterObserver::~CritterObserver() {
    subject->detach(this);
}

void CritterObserver::update() {
    // Display critter information when it changes
    std::cout << "Critter #" << subject->getId() << " Updated:\n";
    std::cout << "  HP: " << subject->getHitpoints() << "\n";
    std::cout << "  Speed: " << subject->getSpeed() << "\n";
    std::cout << "  Position: (" << subject->getX() << ", " << subject->getY() << ")\n";
    std::cout << "  Status: " << (subject->isAlive() ? "Alive" : "Dead") << "\n";
}