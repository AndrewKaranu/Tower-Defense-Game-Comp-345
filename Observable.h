#pragma once
#include <vector>

class Observer;

class Observable {
protected:
    std::vector<Observer*> observers;
public:
    virtual void addObserver(Observer* observer);
    virtual void removeObserver(Observer* observer);
    virtual void notifyObservers();
};