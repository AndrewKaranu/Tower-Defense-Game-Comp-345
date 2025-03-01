#include "CritterGroupObserver.h"
#include <sstream>

CritterGroupObserver::CritterGroupObserver(sf::RenderWindow* window) : window(window) {
    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
    }
}

void CritterGroupObserver::update(Observable* observable) {
    CritterGroup* critterGroup = static_cast<CritterGroup*>(observable);
    draw(critterGroup);
}

void CritterGroupObserver::draw(const CritterGroup* critterGroup) {
    if (!window->isOpen()) return;

    window->clear(sf::Color(50, 50, 50));

    // Draw each critter
    for (auto critter : critterGroup->getAllCritters()) {
        // Draw critter representation
        sf::CircleShape shape(10.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(critter->getX() * 30, critter->getY() * 30);

        // Draw critter info
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);

        std::stringstream ss;
        ss << "ID: " << critter->getId() << "\n"
           << "HP: " << critter->getHitpoints();
        text.setString(ss.str());
        text.setPosition(critter->getX() * 30, critter->getY() * 30 - 30);

        window->draw(shape);
        window->draw(text);
    }

    // Draw group info
    sf::Text groupInfo;
    groupInfo.setFont(font);
    groupInfo.setCharacterSize(16);
    groupInfo.setFillColor(sf::Color::Yellow);

    std::stringstream ss;
    ss << "Total Critters: " << critterGroup->getCritterCount();
    groupInfo.setString(ss.str());
    groupInfo.setPosition(10, 10);

    window->draw(groupInfo);

    window->display();
}