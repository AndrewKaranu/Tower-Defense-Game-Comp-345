#include "mapObserver.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp> 

// Constructor for GuiMapObserver class
// Initializes the base class MapObserver with the map pointer and creates an SFML window
GuiMapObserver::GuiMapObserver(const gameMap* map)
    : MapObserver(map), window(sf::VideoMode(800, 600), "Map View") {}


// Update function to refresh the window and draw objects
void GuiMapObserver::update() {
    // Clears the window with a black background
    window.clear(sf::Color::Black);

    // Creates a rectangle shape to represent a tower
    sf::RectangleShape tower(sf::Vector2f(40, 40));  // 40x40 pixels size for the tower
    tower.setFillColor(sf::Color::Yellow);  // Sets the color of the tower to yellow
    tower.setPosition(100, 100);  // Positions the tower at (100, 100) on the window

    // Draw the tower on the window
    window.draw(tower);

    // Displays the updated contents of the window
    window.display();
}




