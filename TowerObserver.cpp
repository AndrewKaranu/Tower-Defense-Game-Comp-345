#include "TowerObserver.h"
#include <iostream>

TowerObserver::TowerObserver(Tower* t) : subject(t) {
    subject->attach(this);
}

TowerObserver::~TowerObserver() {
    subject->detach(this);
}

void TowerObserver::update() {
    // Display tower information when it changes
    std::cout << "Tower Updated:\n";
    std::cout << "  Level: " << subject->getLevel() << "\n";
    std::cout << "  Power: " << subject->getPower() << "\n";
    std::cout << "  Range: " << subject->getRange() << "\n";
    std::cout << "  Position: (" << subject->getX() << ", " << subject->getY() << ")\n";
}