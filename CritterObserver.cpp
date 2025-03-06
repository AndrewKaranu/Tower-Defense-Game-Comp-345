#include "CritterObserver.h"
#include <iostream>
using namespace std;
CritterObserver::CritterObserver(const std::string& name) : name(name) {
}

void CritterObserver::update(Observable* observable) {
    Critter* critter = static_cast<Critter*>(observable);

    cout << "Observer " << name << " received update for Critter #" << critter->getId() << ":" << endl;
    cout << "  Position: (" << critter->getX() << ", " << critter->getY() << ")" << endl;
    cout << "  Hitpoints: " << critter->getHitpoints() << endl;
    cout << "  Level: " << critter->getLevel() << endl;
    cout << "  Speed: " << critter->getSpeed() << endl;
    cout << "  Strength: " << critter->getStrength() << endl;
    cout << "  Reward: " << critter->getReward() << endl;
    cout << std::endl;
}