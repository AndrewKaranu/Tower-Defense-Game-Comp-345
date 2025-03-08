#pragma once
#include "Observer.h"
#include "critter.h"

/**
 * @brief Observer that displays critter information when the critter changes.
 */
class CritterObserver : public Observer {
private:
    Critter* subject;
    
public:
    CritterObserver(Critter* c);
    ~CritterObserver();
    
    void update() override;
};