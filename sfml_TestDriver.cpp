#include "slow_tower.h"
#include "base_tower.h"
#include "aoe_tower.h"
#include "critter.h"
#include "CritterGroupGenerator.h"
#include "map.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void renderGame(sf::RenderWindow& window, gameMap& myMap) {
    window.clear();
    
    // Draw the map
    myMap.displayMap(window);
    
    // Update window
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(600, 600)), "Tower Defense Game");
    gameMap myMap(5, 5);
    
    myMap.setCell(0, 0, new pathCell());
    myMap.setCell(0, 1, new pathCell());
    myMap.setCell(0, 2, new pathCell());
    myMap.setCell(0, 3, new pathCell());
    myMap.setCell(0, 4, new sceneryCell());
    
    myMap.setEntry(0, 0);
    myMap.setExit(4, 4);
    
    while (window.isOpen()) {
        std::optional<sf::Event> event;
        while (auto event = window.pollEvent()) {
            if (event && event->isType(sf::Event::Closed))
                window.close();
        }
        
        
        renderGame(window, myMap);
    }
    
    return 0;
}