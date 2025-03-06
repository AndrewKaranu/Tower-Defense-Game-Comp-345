#pragma once
#include "Observer.h"
#include "CritterGroup.h"
#include "CritterGroupObserver.h"
#include <string>

class CritterGroupObserver : public Observer {
private:
    std::string name;

public:
    CritterGroupObserver(const std::string& name);
    void update(Observable* observable) override;
};