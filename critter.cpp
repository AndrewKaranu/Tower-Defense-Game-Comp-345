
#include "Critter.h"
#include <iostream>
#include "Observer.h"
#include "Observable.h"

using namespace std;

Critter::Critter() : id(0), hitpoints(0), reward(0), strength(0), speed(0.0), level(0) {}

Critter::Critter(int id, int hitPoints, int reward, int strength, double speed, int level)
    : id(id), hitpoints(hitPoints), reward(reward), strength(strength), speed(speed), level(level) {}

int Critter::getId() const {return id;}
int Critter::getHitpoints() const {return hitpoints;}
int Critter::getReward() const {return reward;}
int Critter::getStrength() const {return strength;}
double Critter::getSpeed() const {return speed;}
int Critter::getLevel() const {return level;}

void Critter::setId(int id) {this->id = id;notifyObservers();}
void Critter::setHitpoints(int hitPoints) {this->hitpoints = hitPoints;notifyObservers();}
void Critter::setReward(int reward) {this->reward = reward;notifyObservers();}
void Critter::setStrength(int strength) {this->strength = strength;notifyObservers();}
void Critter::setSpeed(double speed) {this->speed = speed;notifyObservers();}
void Critter::setLevel(int level) {this->level = level;notifyObservers();}

void Critter::takeDamage(int damage) {
    hitpoints -= damage;
    if (hitpoints < 0) hitpoints = 0;
    notifyObservers();
}

bool Critter::isAlive() const {
    return hitpoints > 0;
}

void Critter::move() {
    cout << "Critter #" << id << "is moving at the speed of " << speed <<" towards the exit!" << endl;
    notifyObservers();
}

void Observable::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Observable::removeObserver(Observer* observer) {
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Critter::notifyObservers() {
    for (auto observer : observers) {
        observer->update(this);
    }
}