// Observable.h
#pragma once
#include <vector>
#include <algorithm>
#include "Observer.h"

class Observable {
private:
    std::vector<Observer*> observers;

protected:
    void notifyObservers() {
        for(Observer* observer : observers) {
            observer->update();
        }
    }

public:
    virtual ~Observable() = default;
    
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }
};