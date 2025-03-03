// CritterGroupObserver.h
#pragma once
#include "Observer.h"
#include "CritterGroup.h"
#include <SFML/Graphics.hpp>

class CritterGroupObserver : public Observer {
private:
    sf::RenderWindow* window;
    sf::Font font;

public:
    CritterGroupObserver(sf::RenderWindow* window);
    void update(Observable* observable) override;
    void draw(const CritterGroup* critterGroup);
};