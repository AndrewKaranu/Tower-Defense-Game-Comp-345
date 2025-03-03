// CritterObserver.h
#pragma once
#include "Observer.h"
#include "Critter.h"
#include <SFML/Graphics.hpp>
#include <string>

class CritterObserver : public Observer {
private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::CircleShape critterShape;
    sf::Text critterInfo;

public:
    CritterObserver(sf::RenderWindow* window);
    void update(Observable* observable) override;
    void draw();
};