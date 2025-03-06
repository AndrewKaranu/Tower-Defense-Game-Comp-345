#pragma once
#include "Observer.h"
#include "critter.h"
#include <string>

class CritterObserver : public Observer {
private:
    std::string name;

public:
    CritterObserver(const std::string& name);
    void update(Observable* observable) override;
};