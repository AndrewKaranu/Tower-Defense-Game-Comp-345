#pragma once
#include <vector>
#include <algorithm>

class Observer;

class Observable {
protected:
    std::vector<Observer*> observers;
public:
    virtual void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    virtual void removeObserver(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    virtual void notifyObservers() = 0;

    virtual ~Observable() = default; // a destructor
};