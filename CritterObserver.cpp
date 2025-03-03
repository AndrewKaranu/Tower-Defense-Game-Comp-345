#include "CritterObserver.h"
#include <sstream>

CritterObserver::CritterObserver(sf::RenderWindow* window) : window(window) {
    // Load font
    if (!font.loadFromFile("arial.ttf")) {

    }

    // Setup critter representation
    critterShape.setRadius(10.f);
    critterShape.setFillColor(sf::Color::Red);

    // Setup text for critter info
    critterInfo.setFont(font);
    critterInfo.setCharacterSize(12);
    critterInfo.setFillColor(sf::Color::White);
}

void CritterObserver::update(Observable* observable) {
    Critter* critter = static_cast<Critter*>(observable);

    // Update position of the shape
    critterShape.setPosition(critter->getX() * 30, critter->getY() * 30); // Scale position

    // Update text information
    std::stringstream ss;
    ss << "ID: " << critter->getId() << "\n"
       << "HP: " << critter->getHitpoints() << "\n"
       << "Level: " << critter->getLevel();
    critterInfo.setString(ss.str());
    critterInfo.setPosition(critter->getX() * 30, critter->getY() * 30 - 30);

    // Redraw the observer view
    draw();
}

void CritterObserver::draw() {
    if (window->isOpen()) {
        window->draw(critterShape);
        window->draw(critterInfo);
    }
}